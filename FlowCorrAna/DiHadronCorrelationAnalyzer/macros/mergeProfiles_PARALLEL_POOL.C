#include <TFile.h>
#include <TDirectory.h>
#include <TKey.h>
#include <TSystem.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TProfile3D.h>

#include <ROOT/TThreadExecutor.hxx>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using HMap = std::map<std::string, TObject*>;

// =========================================================
// Recursively scan directories inside ONE ROOT file
// =========================================================
void ScanDirectory(TDirectory* dir, std::string path, HMap &localMap) {
    TIter nextkey(dir->GetListOfKeys());
    TKey *key;

    while ((key = (TKey*)nextkey())) {
        TObject *obj = key->ReadObj();
        std::string name = key->GetName();
        std::string fullName = (path == "" ? name : path + "/" + name);

        if (obj->InheritsFrom(TDirectory::Class())) {
            ScanDirectory((TDirectory*)obj, fullName, localMap);
        }
        else if (obj->InheritsFrom(TH1::Class()) ||
                 obj->InheritsFrom(TProfile::Class()) ||
                 obj->InheritsFrom(TProfile2D::Class()) ||
                 obj->InheritsFrom(TProfile3D::Class()))
        {
            localMap[fullName] = obj->Clone();
            if (localMap[fullName]->InheritsFrom(TH1::Class()))
                ((TH1*)localMap[fullName])->SetDirectory(nullptr);
        }
    }
}

// =========================================================
// Read directory list
// =========================================================
std::vector<std::string> ReadDirList(const std::string &listfile) {
    std::ifstream in(listfile);
    std::vector<std::string> dirs;
    std::string line;

    while (std::getline(in, line)) {
        if (!line.empty() && line[0] != '#')
            dirs.push_back(line);
    }
    return dirs;
}

// =========================================================
// Get all ROOT files in directory
// =========================================================
std::vector<std::string> ListRootFiles(const std::string &dir) {
    std::vector<std::string> files;

    void *dp = gSystem->OpenDirectory(dir.c_str());
    if (!dp) return files;

    const char *entry;
    while ((entry = gSystem->GetDirEntry(dp))) {
        std::string name = entry;
        if (name.size() > 5 && name.rfind(".root") != std::string::npos)
            files.push_back(dir + "/" + name);
    }
    return files;
}

// =========================================================
// Process a single file (this is executed in parallel)
// =========================================================
HMap ProcessFile(const std::string &filename) {
    HMap localMap;
    TFile *f = TFile::Open(filename.c_str());
    if (!f || f->IsZombie()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return localMap;
    }

    ScanDirectory(f, "", localMap);
    f->Close();

    std::cout << "Processed: " << filename << std::endl;
    return localMap;
}

// =========================================================
// MAIN PARALLEL MERGE FUNCTION (POOL VERSION)
// =========================================================
void mergeProfiles_PARALLEL_POOL(std::string dirlist,
                                 std::string output="merged.root",
                                 int nThreads=8)
{
    TH1::AddDirectory(kFALSE);

    auto dirs = ReadDirList(dirlist);

    std::vector<std::string> allFiles;
    for (auto &d : dirs) {
        auto v = ListRootFiles(d);
        allFiles.insert(allFiles.end(), v.begin(), v.end());
    }

    std::cout << "Found " << allFiles.size() 
              << " ROOT files. Using " << nThreads 
              << " threads.\n";

    // --------------------------------------------------------
    // Parallel processing
    // --------------------------------------------------------
    ROOT::TThreadExecutor pool(nThreads);

    std::vector<HMap> results =
        pool.Map(ProcessFile, allFiles);

    // --------------------------------------------------------
    // Merge maps together
    // --------------------------------------------------------
    HMap finalMap;

    std::cout << "Merging results..." << std::endl;

    for (auto &map : results) {
        for (auto &kv : map) {
            std::string name = kv.first;

            if (!finalMap.count(name)) {
                finalMap[name] = kv.second->Clone(name.c_str());
                if (finalMap[name]->InheritsFrom(TH1::Class()))
                    ((TH1*)finalMap[name])->SetDirectory(nullptr);
            }
            else {
                ((TH1*)finalMap[name])->Add((TH1*)kv.second);
            }
        }
    }

    // --------------------------------------------------------
    // Write merged output
    // --------------------------------------------------------
    std::cout << "Writing merged file: " << output << std::endl;

    TFile *out = new TFile(output.c_str(), "RECREATE");

    for (auto &kv : finalMap) {
        std::string fullpath = kv.first;
        std::string dirpath = fullpath.substr(0, fullpath.find_last_of("/"));
        std::string hname   = fullpath.substr(fullpath.find_last_of("/")+1);

        if (!out->GetDirectory(dirpath.c_str()))
            out->mkdir(dirpath.c_str());

        out->cd(dirpath.c_str());
        kv.second->Write(hname.c_str());
    }

    out->Close();

    std::cout << "Done.\n";
}

