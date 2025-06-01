import pandas as pd
import matplotlib.pyplot as plt

def plot_colored_data(path):
    try:
        df = pd.read_csv(path)
        df['Timestamp(s)'] = df['Timestamp(ms)'] / 1000

        # Define color mapping based on Interval(ms)
        colors = []
        for interval in df['Interval(ms)']:
            if interval < 5000:
                colors.append('#019a7b')
            elif interval < 10000:
                colors.append('#e9dc01')
            else:
                colors.append('#f20028')

        # Scatter plot with colored points
        plt.figure(figsize=(10, 6))
        plt.grid(True)
        scatter = plt.scatter(df['Timestamp(s)'], df['Interval(ms)'], c=colors, marker='o')

        plt.ylim(-1000,20000)

        # Create a legend for the colors
        handles = [plt.Rectangle((0, 0), 1, 1, color=c) for c in ['#019a7b', '#e9dc01', '#f20028']]
        labels = ['< 5000 ms', '5000-10000 ms', '> 10000 ms']
        plt.legend(handles, labels)

        plt.xlabel('Timestamp(s)')
        plt.ylabel('Interval(ms)')
        plt.title('Interval(ms) vs. Timestamp(s) (Colored Data Points)')
        # plt.show()

        # Save the figure
        plt.savefig(r"Test_Record/0501/0501_LoRaTest.png", dpi=1200, bbox_inches='tight')

    except FileNotFoundError:
        print(f"Error: The file '{path}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

path = "Test_Record/0501/0501_LoRaTest.csv"
plot_colored_data(path)