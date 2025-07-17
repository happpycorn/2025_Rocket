import { updateBoolCircles } from './bool-indicator.js';
import { updateTelemetryValues } from './updater.js';
import { updateWarnings } from './warnings.js';
import { updateChart } from './loacl_chart.js';
import { drawGPSPosition } from './gps.js';
import { resizeCanvasToDisplaySize } from './gps.js';
import { drawPitch } from './rocket-viewer.js';
import { resizePitchCanvas } from './rocket-viewer.js';
// 之後 import chart.js / gps.js / rocket-viewer.js

async function fetchData() {
    try {
        const res = await fetch("/data");
        // const res = await fetch("/data/asset/test_data.json");
        const data = await res.json();

        updateBoolCircles(data.rocket_state);
        updateTelemetryValues(data);
        updateWarnings(data.warning);

        if (data.slope_data && data.slope_data.length > 0) {
            updateChart(data.slope_data);
        }

        const rocketLat = data.gps_data[0];
        const rocketLon = data.gps_data[1];
        const gndLat = data.gps_data[2];
        const gndLon = data.gps_data[3];

        // 傳入 draw 函數
        drawGPSPosition([gndLat, gndLon], [rocketLat, rocketLon]);
        drawPitch(data.attit_data[1]);
    } catch (e) {
        console.error("取得資料失敗：", e);
    }
}

// 初次設定
resizeCanvasToDisplaySize();
resizePitchCanvas();
setInterval(fetchData, 1000);
fetchData();

// 若需要監聽視窗大小改變
window.addEventListener("resize", () => {
    resizeCanvasToDisplaySize();
    resizePitchCanvas();
});
