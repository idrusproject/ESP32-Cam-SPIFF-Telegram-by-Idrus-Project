ESP32-CAM Telegram Bot
Proyek ini menggunakan ESP32-CAM untuk mengambil dan mengirim foto ke Telegram melalui bot. Berikut adalah ringkasan singkat dan konfigurasi yang diperlukan untuk memulai proyek ini.

Fitur Utama
Pengambilan dan Pengiriman Foto: Mengambil foto menggunakan ESP32-CAM dan mengirimkannya ke Telegram melalui bot.
Kontrol LED: Menyalakan dan mematikan LED flash pada ESP32-CAM secara remote.
Penghapusan File: Fungsi untuk menghapus semua file yang tersimpan di sistem file SPIFFS.
Konfigurasi Awal
Pin ESP32-CAM: Pastikan pin ESP32-CAM terhubung dengan benar sesuai konfigurasi yang diperlukan.
WiFi: Konfigurasikan SSID dan password WiFi pada kode program.
Token Bot Telegram: Gantikan BOT_TOKEN dan CHAT_ID dengan token bot Telegram dan ID obrolan Anda.
Penggunaan
Instalasi Library: Pastikan semua library yang diperlukan telah diinstal di Arduino IDE.
Upload Kode: Unggah kode ke ESP32-CAM menggunakan Arduino IDE.
Monitor Serial: Pantau output Serial Monitor untuk debug dan informasi status.
Langkah-langkah
Setup: Inisialisasi koneksi WiFi dan konfigurasi perangkat.
Loop: Handle permintaan dari bot Telegram dan kontrol perangkat secara berkelanjutan.
Fungsi Utama
captureAndSavePhoto(): Mengambil foto dari kamera dan menyimpannya di sistem file SPIFFS.
sendPhotoTelegramSpiff(): Mengirim foto yang tersimpan di SPIFFS ke bot Telegram menggunakan multipart/form-data.
Catatan
Pastikan ESP32-CAM terhubung dengan WiFi untuk komunikasi dengan server Telegram.
Periksa status koneksi WiFi dan sensor kamera melalui output Serial Monitor untuk debug.
Proyek ini memanfaatkan sistem file SPIFFS untuk penyimpanan sementara sebelum pengiriman ke Telegram.
Dokumentasi ini membantu memahami dan mengintegrasikan ESP32-CAM dengan Telegram Bot. Sesuaikan konfigurasi dan ikuti langkah-langkah sesuai kebutuhan Anda.
