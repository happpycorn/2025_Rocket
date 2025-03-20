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
    get_keys = ["时间 (s)", "高度 (m)", "垂直速度 (m/s)"]
    data = read_csv(file_path)
    
    time, high, ver = [], [], []
    
    for row in data:
        
        try:
            time.append(float(row[get_keys[0]]))
            high.append(float(row[get_keys[1]]))
            ver.append(float(row[get_keys[2]]))
        except ValueError:
            continue  # 跳過無效數據
    
    # 使用 subplots 創建圖表
    fig, ax1 = plt.subplots(figsize=(8, 5))
    
    ax1.plot(time, high, label='High (m)', color="#019a7b")
    ax1.axhline(0, color="black", linestyle="--", linewidth=1)
    
    ax1.set_xlabel("Time (s)")
    ax1.set_ylabel("High (m)")
    ax1.set_title("High, Vertical speed with Time")
    ax1.set_ylim(-216, 1300)
    ax1.tick_params(axis='y', labelcolor="#019a7b")
    ax1.grid()

    ax2 = ax1.twinx()
    ax2.plot(time, ver, label="Vertical Speed (m/s)", color="#1f318f", linestyle="--")
    ax2.set_ylabel("Vertical Speed (m/s)")
    ax2.set_ylim(-30, 180)
    ax2.tick_params(axis='y', labelcolor="#1f318f")

    ax1.legend(loc="upper right", bbox_to_anchor=(1, 1))
    ax2.legend(loc="upper right", bbox_to_anchor=(1, 0.9))
    
    plt.show()

    plt.savefig('output_chart.png', dpi=300, bbox_inches='tight')  # 儲存為 PNG 格式

# 測試用範例
if __name__ == "__main__":
    file_path = "Simular_Data/ko.csv"  # 請替換為你的 CSV 檔案路徑
    plot_data(file_path)
