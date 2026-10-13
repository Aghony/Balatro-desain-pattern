#ifndef HAND_PLAYER_H
#define HAND_PLAYER_H

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Hand.h"

// Pemain memilih kartu mana yang dimainkan dari tangan yang dibagikan (seperti Balatro).
// Mode interaktif: pemain mengetik nomor kartu. Mode otomatis: 5 kartu pertama.
class HandPlayer {
private:
    bool interactive;
    std::istream* in;
    std::ostream* out;

    // Mengubah "1 3 5" menjadi daftar nomor kartu (dimulai dari 1). false + pesan jika tidak valid.
    static bool parseChoice(const std::string& line, int handSize,
                            std::vector<int>& result, std::string& error) {
        result.clear();
        std::set<int> seen;
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            int n = 0;
            try {
                size_t used = 0;
                n = std::stoi(token, &used);
                if (used != token.size()) throw std::invalid_argument("x");
            } catch (...) {
                error = "Masukkan hanya angka, dipisah spasi.";
                return false;
            }
            if (n < 1 || n > handSize) {
                error = "Nomor kartu harus antara 1 dan " + std::to_string(handSize) + ".";
                return false;
            }
            if (!seen.insert(n).second) {
                error = "Kartu " + std::to_string(n) + " dipilih dua kali.";
                return false;
            }
            result.push_back(n);
        }
        if (result.empty() || result.size() > static_cast<size_t>(MAX_PLAY)) {
            error = "Pilih 1 sampai " + std::to_string(MAX_PLAY) + " kartu.";
            return false;
        }
        return true;
    }

    static Hand firstCards(const Hand& dealt) {
        Hand h;
        for (size_t i = 0; i < dealt.cards.size() && i < static_cast<size_t>(MAX_PLAY); ++i) {
            h.cards.push_back(dealt.cards[i]);
        }
        return h;
    }

public:
    static const int MAX_PLAY = 5;

    explicit HandPlayer(bool interactiveMode = true,
                        std::istream& input = std::cin,
                        std::ostream& output = std::cout)
        : interactive(interactiveMode), in(&input), out(&output) {}

    Hand play(const Hand& dealt) {
        if (!interactive) {
            return firstCards(dealt);
        }

        *out << "  [DEAL] ";
        for (size_t i = 0; i < dealt.cards.size(); ++i) {
            *out << (i + 1) << ":" << ToString(dealt.cards[i]) << "  ";
        }
        *out << "\n";

        while (true) {
            *out << "  Pilih 1-" << MAX_PLAY << " kartu (nomor dipisah spasi, contoh: 1 3 4): " << std::flush;

            std::string line;
            if (!std::getline(*in, line)) {
                *out << "\n  [input habis] memainkan " << MAX_PLAY << " kartu pertama\n";
                return firstCards(dealt);
            }

            std::vector<int> choice;
            std::string error;
            if (parseChoice(line, static_cast<int>(dealt.cards.size()), choice, error)) {
                Hand chosen;
                for (int n : choice) {
                    chosen.cards.push_back(dealt.cards[n - 1]);
                }
                return chosen;
            }
            *out << "  ! " << error << "\n";
        }
    }
};

#endif
