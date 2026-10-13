# balatro-replica # DP-Week1-5225600037-Justin

## Task 3 - Chain of Responsibility

`RunSession` dari Task 1 dipertahankan sebagai pengatur alur (setara `Game Manager` di diagram).
Kelas-kelas diagram dibungkus adapter (`PokerAdapters.h`) agar memenuhi interface Task 1.

| Interface Task 1 | Adapter | Membungkus |
|---|---|---|
| IInputGenerator | PokerInputGenerator | HandGenerator + HandPlayer |
| IScoringRule | PokerScoringRule | ScoringRule (rantai Flush/Straight) |
| IRewardRule | BlindRewardRule | BlindRule + RewardRule |

## Compile & jalankan
```
g++ -std=c++17 -o balatro main.cpp RunSession.cpp
./balatro                 # pemain memilih kartu sendiri
./balatro --auto          # otomatis (tanpa input)
./balatro --decks=3       # 3 dek: Five of a Kind & Flush House bisa muncul
```
(`program.exe` lama dari Task 1 tidak berlaku untuk versi ini; compile ulang.)

## Perubahan terhadap file Task 1
- `InputGenerator.h`: `TurnInput` ditambah `Hand hand = {};`
- `RunSession.h` / `RunSession.cpp`: TIDAK berubah.
- `ScoringRule.h` / `RewardRule.h` (Task 1) tetap; versi diagram bernama `PokerScoring.h` / `PokerReward.h`.

## 12 peringkat tangan
High Card, Pair, Two Pair, Three of a Kind, Straight, Flush, Full House, Four of a Kind,
Straight Flush, Royal Flush, Five of a Kind, Flush House: tabel aturan dan skor ada di README
`1_diagram_GameManager`. Five of a Kind dan Flush House butuh kartu kembar, jadi hanya muncul
dengan `--decks=2` / `--decks=3`.

## Perilaku
Target blind 35, 50, 65. Blind yang gagal memberi reward 0 tetapi run lanjut sampai 3 ronde (loop RunSession tetap).
Versi 1 (`1_diagram_GameManager`) mengakhiri run saat blind gagal.

## Refleksi (versi gabungan)
1. **Invariant**: urutan 6 fase di `RunSession::StartRun()` (generate input, base score, reward,
   update money, shop, advance round) tetap sama walau seluruh isi game berganti menjadi poker.
2. **Mutable**: cara membuat tangan (HandGenerator/HandPlayer), rumus skor (rantai checker + chip kartu),
   aturan blind & reward, dan isi shop. Semuanya di balik interface.
3. **Mengapa RunSession tidak berubah**: ia hanya mengenal `IInputGenerator`, `IScoringRule`,
   `IRewardRule`. Tiga strategi diganti sekaligus cukup lewat `main.cpp` (Dependency Injection).
4. **Jika logika skor ada di RunSession**: aturan poker (Flush, Straight, blind) akan menumpuk di
   loop utama; setiap perubahan aturan berisiko merusak urutan fase dan melanggar Single Responsibility.

## Cara bermain (pemain memilih kartu)
`PokerInputGenerator` membagikan 8 kartu; `HandPlayer` meminta pemain mengetik 1-5 nomor kartu
(contoh: `1 3 4 6 7`). Input salah diminta ulang. `./balatro --auto` memainkan 5 kartu pertama tanpa input.
`RunSession` tetap tidak berubah; pilihan pemain terjadi di dalam tahap "Generate Input".
