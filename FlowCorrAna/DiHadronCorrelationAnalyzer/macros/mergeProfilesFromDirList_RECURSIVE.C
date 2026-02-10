#include <TFile.h>
#include <TDirectory.h>
#include <TKey.h>
#include <TSystem.h>
#include <TH1.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TProfile3D.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

std::map<std::string, TObject*> mergedMap;

// ================================================================
// Recursively scan ROOT file directories and merge all histograms
// ================================================================
void MergeDirectoryRecursive(TDirectory *target, TDirectory *source, std::string path="") {
    source->cd();
    TIter nextkey(source->GetListOfKeys());
    TKey *key;

    while ((key = (TKey*)nextkey())) {
        TObject *obj = key->ReadObj();
        std::string name = key->GetName();
        std::string fullName = (path == "" ? name : path + "/" + name);

        // Subdirectory → recurse
        if (obj->InheritsFrom(TDirectory::Class())) {
            TDirectory *subSrc = (TDirectory*)obj;

            TDirectory *subTgt = (TDirectory*)target->Get(name.c_str());
            if (!subTgt)
                subTgt = target->mkdir(name.c_str());

            MergeDirectoryRecursive(subTgt, subSrc, fullName);
        }

        // Histograms merge
        else if (obj->InheritsFrom(TH1::Class()) ||
                 obj->InheritsFrom(TProfile::Class()) ||
                 obj->InheritsFrom(TProfile2D::Class()) ||
                 obj->InheritsFrom(TProfile3D::Class()))
        {
            if (!mergedMap.count(fullName)) {
                mergedMap[fullName] = obj->Clone(fullName.c_str());
                if (mergedMap[fullName]->InheritsFrom(TH1::Class()))
                    ((TH1*)mergedMap[fullName])->SetDirectory(nullptr);
            } 
            else {
                ((TH1*)mergedMap[fullName])->Add((TH1*)obj);
            }
        }
    }
}

// ================================================================
// Read directories from text file
// ================================================================
std::vector<std::string> ReadDirectoryList(const std::string& listfile) {
    std::ifstream in(listfile);
    std::vector<std::string> dirs;
    std::string line;

    if (!in.is_open()) {
        std::cerr << "ERROR: Cannot open directory list: " << listfile << std::endl;
        return dirs;
    }

    while (std::getline(in, line)) {
        if (line.empty() || line[0]=='#') continue;
        dirs.push_back(line);
    }

    return dirs;
}

// ================================================================
// Utility: list ROOT files inside directory
// ================================================================
std::vector<std::string> GetRootFiles(const std::string& dir) {
    std::vector<std::string> files;

    void* dp = gSystem->OpenDirectory(dir.c_str());
    if (!dp) return files;

    const char* entry;
    while ((entry = gSystem->GetDirEntry(dp))) {
        std::string name = entry;
        if (name == "." || name == "..") continue;

        if (name.rfind(".root") != std::string::npos)
            files.push_back(dir + "/" + name);
    }

    return files;
}

// ================================================================
// MAIN MERGING FUNCTION (QUIET)
// ================================================================
void mergeProfilesFromDirList_RECURSIVE(std::string dirlist,
                                              std::string output="merged.root")
{
    mergedMap.clear();

    auto dirs = ReadDirectoryList(dirlist);

    for (auto &d : dirs) {
        auto files = GetRootFiles(d);

        for (auto &f : files) {
            std::cout << "Processing ROOT file: " << f << std::endl;

            TFile *fin = TFile::Open(f.c_str());
            if (!fin || fin->IsZombie()) {
                std::cerr << "  ERROR opening file\n";
                continue;
            }

            MergeDirectoryRecursive(fin, fin);  
            fin->Close();
        }
    }

    // ============================================================
    // Write output
    // ============================================================
    std::cout << "\nWriting merged output → " << output << std::endl;

    TFile *fout = new TFile(output.c_str(), "RECREATE");

    for (auto &kv : mergedMap) {
        std::string fullpath = kv.first;
        std::string dirpath = fullpath.substr(0, fullpath.find_last_of("/"));
        std::string hname   = fullpath.substr(fullpath.find_last_of("/")+1);

        if (!fout->GetDirectory(dirpath.c_str()))
            fout->mkdir(dirpath.c_str());

        fout->cd(dirpath.c_str());
        kv.second->Write(hname.c_str());
    }

    fout->Close();

    std::cout << "Merge complete.\n";
}

