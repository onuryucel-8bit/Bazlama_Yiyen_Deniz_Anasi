from pathlib import Path
import math

#proje
project_dir = Path(__file__).resolve().parent.parent

#proje/out
out_dir = project_dir / "out"

#proje/out/kernel.bin
kernel_file = out_dir / "kernel.bin"

#proje/boot
boot_dir = project_dir / "boot"

#proje/boot/SektorSayisi.asm
sektorSayisi_asm = boot_dir / "SektorSayisi.asm"

#---------------------------------------#
dosyaBoyutu = kernel_file.stat().st_size
sektorSayisi = math.ceil(dosyaBoyutu / 512)
dosyaBoyutu_kb = dosyaBoyutu / 1024
#---------------------------------------#

print("====================================")
print("Sektor sayisi hesaplaniyor...")
#print("Kabak cekirdegi :", kernel_file, "\n")
print("Dosya boyutu :", dosyaBoyutu, "bayt")
print("Dosya boyutu :", dosyaBoyutu_kb, "kb : kilo bayt")
print("Sektor adeti:", sektorSayisi)

with open(sektorSayisi_asm, "w") as f:
  f.write(f"%define SEKTOR_ADETI {sektorSayisi}")

#0x9'fc00 - 0x7'e00 = 0x9'7E00 (622.080 bayt)
#622.080 / 1024 = 607 kb
#1215 sektor