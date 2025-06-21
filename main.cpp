#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

map<string, string> extensionMap = {
    {".jpg", "Images"}, {".png", "Images"}, {".jpeg", "Images"},
    {".mp4", "Videos"}, {".mov", "Videos"}, {".avi", "Videos"},
    {".pdf", "Documents"}, {".docx", "Documents"}, {".txt", "Documents"},
    {".zip", "Zips"}, {".rar", "Zips"}
};

void organize(const fs::path& folderPath) {
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        cerr << "❌ Invalid folder path!\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            string ext = entry.path().extension().string();
            if (extensionMap.count(ext)) {
                fs::path destDir = folderPath / extensionMap[ext];
                fs::create_directories(destDir);
                fs::path destFile = destDir / entry.path().filename();
                fs::rename(entry.path(), destFile);  // Move file
                cout << "✅ Moved: " << entry.path().filename() << " → " << extensionMap[ext] << "\n";
            }
        }
    }
}

int main() {
    string folder;
    cout << "📂 Enter full folder path to organize: ";
    getline(cin, folder);

    organize(fs::path(folder));
    cout << "🎉 Done organizing!\n";
}
