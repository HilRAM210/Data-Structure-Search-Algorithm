#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Paper {
    string source;
    string topic;
    string title;
    string author;
    int year;
};

vector<Paper> papers;
bool isDataLoaded = false;

vector<Paper> sortedByTitle;
vector<Paper> sortedByAuthor;
vector<Paper> sortedByYear;
bool indexesBuilt = false;

void loadData() {
    string filename = "papers.csv";

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Gagal membuka file " << filename << endl;
        getch();
        system("cls");
        return;
    }

    papers.clear();
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 8 && !tokens[5].empty()) {
            Paper paper;
            paper.source = tokens[3];
            paper.topic = tokens[4];
            paper.title = tokens[5];
            try {
                paper.year = stoi(tokens[6]);
            } catch (...) {
                paper.year = 0;
            }
            paper.author = tokens[7];
            papers.push_back(paper);
        }
    }

    file.close();
    isDataLoaded = true;
    indexesBuilt = false;
    cout << "Data berhasil dimuat! Total paper: " << papers.size() << endl;
    getch();
    system("cls");
}

void buildIndexes() {
    if (!isDataLoaded) return;
    
    auto startTime = high_resolution_clock::now();
    
    sortedByTitle = papers;
    sortedByAuthor = papers;
    sortedByYear = papers;
    
    sort(sortedByTitle.begin(), sortedByTitle.end(), [](const Paper& a, const Paper& b) {
        return a.title < b.title;
    });
    
    sort(sortedByAuthor.begin(), sortedByAuthor.end(), [](const Paper& a, const Paper& b) {
        return a.author < b.author;
    });
    
    sort(sortedByYear.begin(), sortedByYear.end(), [](const Paper& a, const Paper& b) {
        return a.year < b.year;
    });
    
    indexesBuilt = true;
}

void displayAllData() {
    if (!isDataLoaded) {
        cout << "Data belum dimuat. Silakan pilih menu 1 terlebih dahulu." << endl;
        getch();
        system("cls");
        return;
    }
	
	system("cls");
    cout << "\n=========================================================================================================================================" << endl;
    cout << "|                                                       DAFTAR PAPER ILMIAH                                                             |" << endl;
    cout << "=========================================================================================================================================" << endl;
    cout << "| " << left << setw(15) << "Sumber" << " | " 
         << setw(25) << "Topik" << " | " 
         << setw(50) << "Judul" << " | " 
         << setw(25) << "Penulis" << " | " 
         << setw(6) << "Tahun" << " |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (const auto& paper : papers) {
        cout << "| " << left << setw(15) << (paper.source.length() > 15 ? paper.source.substr(0, 12) + "..." : paper.source) << " | " 
             << setw(25) << (paper.topic.length() > 25 ? paper.topic.substr(0, 22) + "..." : paper.topic) << " | " 
             << setw(50) << (paper.title.length() > 50 ? paper.title.substr(0, 47) + "..." : paper.title) << " | " 
             << setw(25) << (paper.author.length() > 25 ? paper.author.substr(0, 22) + "..." : paper.author) << " | " 
             << setw(6) << paper.year << " |" << endl;
    }
    cout << "=========================================================================================================================================" << endl;
    cout << "Total paper: " << papers.size() << endl << endl;
    getch();
    system("cls");
}

vector<Paper> linearSearchByTitle(const string& title) {
    auto startTime = high_resolution_clock::now();
    
    vector<Paper> results;
    for (const auto& paper : papers) {
        string lowerTitle = paper.title;
        string lowerSearch = title;
        transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
        
        if (lowerTitle.find(lowerSearch) != string::npos) {
            results.push_back(paper);
        }
    }
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    
    cout << "\n=========================================================================================================================================\n" << endl;
    cout << "Pencarian selesai dalam " << duration.count() / 1000000.0 << " ms" << endl;
    return results;
}

vector<Paper> linearSearchByYear(int year) {
    auto startTime = high_resolution_clock::now();
    
    vector<Paper> results;
    for (const auto& paper : papers) {
        if (paper.year == year) {
            results.push_back(paper);
        }
    }
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    
    cout << "\n=========================================================================================================================================\n" << endl;
    cout << "Pencarian selesai dalam " << duration.count() / 1000000.0 << " ms" << endl;
    return results;
}

vector<Paper> linearSearchByAuthor(const string& author) {
    auto startTime = high_resolution_clock::now();
    
    vector<Paper> results;
    for (const auto& paper : papers) {
        string lowerAuthor = paper.author;
        string lowerSearch = author;
        transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
        transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
        
        if (lowerAuthor.find(lowerSearch) != string::npos) {
            results.push_back(paper);
        }
    }
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    
    cout << "\n=========================================================================================================================================\n" << endl;
    cout << "Pencarian selesai dalam " << duration.count() / 1000000.0 << " ms" << endl;
    return results;
}

vector<Paper> binarySearchByTitle(const string& title) {
    if (!indexesBuilt) {
        buildIndexes();
    }
    
    auto startTime = high_resolution_clock::now();
    vector<Paper> results;
    
    string lowerSearch = title;
    transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
    
    size_t first = 0;
    size_t last = sortedByTitle.size();
    
    if (lowerSearch.empty()) {
        return sortedByTitle;
    }
    
    while (first < last) {
        size_t mid = first + (last - first) / 2;
        
        string lowerTitle = sortedByTitle[mid].title;
        transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        
        if (lowerTitle < lowerSearch) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    
    for (size_t i = 0; i < sortedByTitle.size(); ++i) {
        string lowerTitle = sortedByTitle[i].title;
        transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        
        if (lowerTitle.find(lowerSearch) != string::npos) {
            results.push_back(sortedByTitle[i]);
        }
    }
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    
    cout << "\n=========================================================================================================================================\n" << endl;
    cout << "Pencarian selesai dalam " << duration.count() / 1000000.0 << " ms" << endl;
    return results;
}

vector<Paper> binarySearchByAuthor(const string& author) {
    if (!indexesBuilt) {
        buildIndexes();
    }
    
    auto startTime = high_resolution_clock::now();
    vector<Paper> results;
    
    string lowerSearch = author;
    transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
    
    size_t first = 0;
    size_t last = sortedByAuthor.size();
    
    if (lowerSearch.empty()) {
        return sortedByAuthor;
    }
    
    while (first < last) {
        size_t mid = first + (last - first) / 2;
        
        string lowerAuthor = sortedByAuthor[mid].author;
        transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
        
        if (lowerAuthor < lowerSearch) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    
    for (size_t i = 0; i < sortedByAuthor.size(); ++i) {
        string lowerAuthor = sortedByAuthor[i].author;
        transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
        
        if (lowerAuthor.find(lowerSearch) != string::npos) {
            results.push_back(sortedByAuthor[i]);
        }
    }
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    
    cout << "\n=========================================================================================================================================\n" << endl;
    cout << "Pencarian selesai dalam " << duration.count() / 1000000.0 << " ms" << endl;
    return results;
}

vector<Paper> binarySearchByYear(int year) {
    if (!indexesBuilt) {
        buildIndexes();
    }
    
    auto startTime = high_resolution_clock::now();
    vector<Paper> results;
    
    auto low = lower_bound(sortedByYear.begin(), sortedByYear.end(), year,
        [](const Paper& paper, int value) {
            return paper.year < value;
        });
    
    auto high = upper_bound(sortedByYear.begin(), sortedByYear.end(), year,
        [](int value, const Paper& paper) {
            return value < paper.year;
        });
    
    for (auto it = low; it != high; ++it) {
        results.push_back(*it);
    }
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    
    cout << "\n=========================================================================================================================================\n" << endl;
    cout << "Pencarian selesai dalam " << duration.count() / 1000000.0 << " ms" << endl;
    return results;
}

void displaySearchResults(const vector<Paper>& results, const string& searchType) {
    if (results.empty()) {
        cout << "Tidak ditemukan hasil yang sesuai." << endl;
        getch();
    	system("cls");
        return;
    }

    cout << "\n=========================================================================================================================================" << endl;
    cout << "|                                   HASIL PENCARIAN " << searchType << endl;
    cout << "=========================================================================================================================================" << endl;
    cout << "| " << left << setw(15) << "Sumber" << " | " 
         << setw(25) << "Topik" << " | " 
         << setw(50) << "Judul" << " | " 
         << setw(25) << "Penulis" << " | " 
         << setw(6) << "Tahun" << " |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (const auto& paper : results) {
        cout << "| " << left << setw(15) << (paper.source.length() > 15 ? paper.source.substr(0, 12) + "..." : paper.source) << " | " 
             << setw(25) << (paper.topic.length() > 25 ? paper.topic.substr(0, 22) + "..." : paper.topic) << " | " 
             << setw(50) << (paper.title.length() > 50 ? paper.title.substr(0, 47) + "..." : paper.title) << " | " 
             << setw(25) << (paper.author.length() > 25 ? paper.author.substr(0, 22) + "..." : paper.author) << " | " 
             << setw(6) << paper.year << " |" << endl;
    }
    cout << "=========================================================================================================================================" << endl;
    cout << "Total ditemukan: " << results.size() << " paper" << endl << endl;
    getch();
    system("cls");
}

void linearSearchMenu() {
    int choice;
    string searchTerm;
    int searchYear;

    while (true) {
    	system("cls");
        cout << "\n=== MENU LINEAR SEARCH ===" << endl;
        cout << "1. Cari berdasarkan Judul" << endl;
        cout << "2. Cari berdasarkan Tahun" << endl;
        cout << "3. Cari berdasarkan Penulis" << endl;
        cout << "0. Kembali ke menu utama" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
        	system("cls");
			break;
		}

        switch (choice) {
            case 1:
                cout << "Masukkan kata kunci judul: ";
                getline(cin, searchTerm);
                displaySearchResults(linearSearchByTitle(searchTerm), "BERDASARKAN JUDUL (LINEAR SEARCH)                                                   |");
                break;
            case 2:
                cout << "Masukkan tahun terbit: ";
                cin >> searchYear;
                displaySearchResults(linearSearchByYear(searchYear), "BERDASARKAN TAHUN (LINEAR SEARCH)                                                   |");
                break;
            case 3:
                cout << "Masukkan nama penulis: ";
                getline(cin, searchTerm);
                displaySearchResults(linearSearchByAuthor(searchTerm), "BERDASARKAN PENULIS (LINEAR SEARCH)                                                 |");
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                getch();
        }
    }
}

void binarySearchMenu() {
    if (!isDataLoaded) {
        cout << "Data belum dimuat. Silakan pilih menu 1 terlebih dahulu." << endl;
        getch();
        system("cls");
        return;
    }
    
    if (!indexesBuilt) {
        buildIndexes();
    }
    
    int choice;
    string searchTerm;
    int searchYear;

    while (true) {
    	system("cls");
        cout << "\n=== MENU BINARY SEARCH ===" << endl;
        cout << "1. Cari berdasarkan Judul" << endl;
        cout << "2. Cari berdasarkan Tahun" << endl;
        cout << "3. Cari berdasarkan Penulis" << endl;
        cout << "0. Kembali ke menu utama" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
        	system("cls");
			break;
		}

        switch (choice) {
            case 1:
                cout << "Masukkan kata kunci judul: ";
                getline(cin, searchTerm);
                displaySearchResults(binarySearchByTitle(searchTerm), "BERDASARKAN JUDUL (BINARY SEARCH)                                                   |");
                break;
            case 2:
                cout << "Masukkan tahun terbit: ";
                cin >> searchYear;
                displaySearchResults(binarySearchByYear(searchYear), "BERDASARKAN TAHUN (BINARY SEARCH)                                                   |");
                break;
            case 3:
                cout << "Masukkan nama penulis: ";
                getline(cin, searchTerm);
                displaySearchResults(binarySearchByAuthor(searchTerm), "BERDASARKAN PENULIS (BINARY SEARCH)                                                 |");
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                getch();
        }
    }
}

void mainMenu() {
    int choice;

    while (true) {
        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Muat Data" << endl;
        cout << "2. Tampilkan Semua Data" << endl;
        cout << "3. Pencarian" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1:
                loadData();
                break;
            case 2:
                displayAllData();
                break;
            case 3: {
                if (!isDataLoaded) {
                    cout << "Data belum dimuat. Silakan pilih menu 1 terlebih dahulu." << endl;
                    getch();
                    system("cls");
                    break;
                }
                
                int searchChoice;
                system("cls");
                cout << "\n=== MENU PENCARIAN ===" << endl;
                cout << "1. Linear Search" << endl;
                cout << "2. Binary Search" << endl;
                cout << "0. Kembali" << endl;
                cout << "Pilihan Anda: ";
                cin >> searchChoice;
                cin.ignore();

                if (searchChoice == 1) linearSearchMenu();
                else if (searchChoice == 2) binarySearchMenu();
                else if (searchChoice == 0) {
        			system("cls");
					break;
				}
                else {
                    cout << "Pilihan tidak valid!" << endl;
                    getch();
                    system("cls");
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid!" << endl;
                getch();
                system("cls");
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
