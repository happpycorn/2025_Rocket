let chart = null; // 全域變數，儲存圖表實體

export function updateChart(slopeData) {
    const times = slopeData.map(row => (row[0] / 1000).toFixed(2)); // x 軸：時間（轉成秒）
    const altitudes = slopeData.map(row => row[1]);
    const velocities = slopeData.map(row => row[2]);
    const accelerations = slopeData.map(row => row[3]);

    const ctx = document.getElementById("dataChart").getContext("2d");

    if (chart) {
        // 若圖表已存在，更新資料
        chart.data.labels = times;
        chart.data.datasets[0].data = altitudes;
        chart.data.datasets[1].data = velocities;
        chart.data.datasets[2].data = accelerations;
        chart.update();
    } else {
        // 建立新圖表
        chart = new Chart(ctx, {
            type: "line",
            data: {
                labels: times,
                datasets: [
                    {
                        label: "高度 (m)",
                        data: altitudes,
                        borderColor: "#4caf50",
                        fill: false
                    },
                    {
                        label: "速度 (m/s)",
                        data: velocities,
                        borderColor: "#2196f3",
                        fill: false
                    },
                    {
                        label: "加速度 (m/s²)",
                        data: accelerations,
                        borderColor: "#ff9800",
                        fill: false
                    }
                ]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                animation: false,
                scales: {
                    x: {
                        title: { display: true, text: "時間 (s)" }
                    },
                    y: {
                        title: { display: true, text: "數值" }
                    }
                },
                plugins: {
                    legend: {
                        labels: {
                            color: "#ddd"
                        }
                    }
                }
            }
        });
    }
}
