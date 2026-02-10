#!/usr/bin/env python3
import json, argparse, csv

def merge(lumis):
    merged = []
    for ls in sorted(lumis):
        if not merged or ls > merged[-1][1] + 1:
            merged.append([ls, ls])
        else:
            merged[-1][1] = ls
    return merged

def main():
    parser = argparse.ArgumentParser(description="Split golden JSON into μ bins (from lumi CSV)")
    parser.add_argument("-j", "--json", required=True, help="Golden JSON (Cert*.json)")
    parser.add_argument("-l", "--lumi", required=True, help="brilcalc lumi --byls --output-style csv file")
    parser.add_argument("-b", "--bins", nargs="+", type=float, required=True,
                        help="Bin edges for μ (e.g. 0 0.14 0.18 0.5)")
    parser.add_argument("--sigma", type=float, required=True,
                        help="Inelastic cross section in nb (e.g. 1.6e9 for 1.6 barn)")
    parser.add_argument("--fbx", type=float, default=11245.0,
                        help="BX frequency in Hz (default 11245 for 25ns)")
    args = parser.parse_args()

    with open(args.json) as f:
        golden = json.load(f)

    # Compute μ per run/LS from CSV
    pileup = {}
    print("Run   LS   μ")
    for row in csv.reader(open(args.lumi)):
        if not row or row[0].startswith("#"): 
            continue
        run = int(row[0].split(":")[0])
        ls = int(row[1].split(":")[0])
        avgdel = float(row[5])  # avgdelivered(/hz/nb)
        mu = avgdel * args.sigma / args.fbx
        pileup.setdefault(run, {})[ls] = mu
        print(f"{run:<6} {ls:<4} {mu:.3f}")

    edges = args.bins
    out = {f"OO_bin{i}.json": {} for i in range(len(edges)-1)}

    for run_str, lumis in golden.items():
        run = int(run_str)
        for start, end in lumis:
            for ls in range(start, end+1):
                if run in pileup and ls in pileup[run]:
                    mu = pileup[run][ls]
                    for i in range(len(edges)-1):
                        if edges[i] <= mu < edges[i+1]:
                            out[f"OO_bin{i}.json"].setdefault(run_str, []).append([ls, ls])

    for fname, content in out.items():
        for run in content:
            content[run] = merge([ls for pair in content[run] for ls in range(pair[0], pair[1]+1)])
        with open(fname, "w") as f:
            json.dump(content, f, indent=2, sort_keys=True)
        print(f"Wrote {fname}")

if __name__ == "__main__":
    main()
