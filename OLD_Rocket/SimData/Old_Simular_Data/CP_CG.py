import csv
import matplotlib.pyplot as plt

def read_csv(file_path):
    """
    讀取 CSV 檔案並回傳內容。
    :param file_path: CSV 檔案路徑
    :return: 內容列表，每一行為一個字典
    """
    with open(file_path, newline='', encoding='utf-8') as csvfile:
        reader = csv.DictReader(csvfile)
        return [row for row in reader]

def plot_data(file_path):
    get_keys = ["时间 (s)", "CP 压心位置 (cm)", "CG 重心位置 (cm)", "稳定裕量 (​)"]
    data = read_csv(file_path)
    
    time, cp, cg, stability_margin = [], [], [], []
    
    for row in data:
        if row.get(get_keys[2]) == "NaN":
            break
        
        try:
            time.append(float(row[get_keys[0]]))
            cp.append(float(row[get_keys[1]]))
            cg.append(float(row[get_keys[2]]))
            stability_margin.append(float(row[get_keys[3]]))
        except ValueError:
            continue  # 跳過無效數據
    
    # 使用 subplots 創建圖表
    fig, ax1 = plt.subplots(figsize=(8, 5))
    
    ax1.plot(time, cp, label="CP's Pos (cm)", color="#019a7b")
    ax1.plot(time, cg, label="CG's Pos (cm)", color="#e9dc01")
    
    ax1.set_xlabel("Time (s)")
    ax1.set_ylabel("Pos (cm)")
    ax1.set_title("CP, CG with Time")
    ax1.legend(loc="upper left")
    ax1.grid()

    ax2 = ax1.twinx()
    ax2.plot(time, stability_margin, label="Stability", color="#1f318f", linestyle="--")
    ax2.set_ylabel("Stability (cal)")
    ax2.legend(loc="upper right")
    
    plt.show()

    plt.savefig('output_chart.png', dpi=300, bbox_inches='tight')  # 儲存為 PNG 格式

# 測試用範例
if __name__ == "__main__":
    file_path = "Simular_Data/ko.csv"  # 請替換為你的 CSV 檔案路徑
    plot_data(file_path)
