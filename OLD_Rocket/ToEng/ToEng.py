import pandas as pd

# --- 設定檔案路徑 ---
input_file = r"Program/ToEng/20250325_Pioneer-5K thrust curve.xlsx - Average F.csv"   # 或是 data.csv
output_file = "output.eng"

# --- 讀取資料 ---
if input_file.endswith(".csv"):
    df = pd.read_csv(input_file)
else:
    df = pd.read_excel(input_file)

# --- 檢查欄位名稱 ---
if df.shape[1] < 2:
    raise ValueError("檔案中需要至少兩欄資料（如：時間與數值）")

df.iloc[:, 1] = df.iloc[:, 1] * 9.80665

# --- 設定 .eng 第一行資訊 ---
eng_header = "Pioneer-5K 109 590 0 9.0 13.5 Fhehs-0630\n"

# --- 寫入 .eng 檔案 ---
with open(output_file, "w") as f:
    f.write(eng_header)
    for index, row in df.iterrows():
        f.write(f"{row[0]:.3f}\t{row[1]:.9f}\n")

print("轉換完成，輸出檔案：", output_file)
