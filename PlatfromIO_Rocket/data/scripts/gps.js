const canvas = document.getElementById("gpsCanvas");
const ctx = canvas.getContext("2d");

const magnification = 3;

export function drawGPSPosition(gps1, gps2) {

    const latA = gps1[0];
    const latB = gps2[0];
    const lonA = gps1[1];
    const lonB = gps2[1];

    const R = 6371000; // 地球半徑（公尺）
    const dLat = (latB - latA) * Math.PI / 180;
    const dLon = (lonB - lonA) * Math.PI / 180;
    const a = 
        Math.sin(dLat/2) * Math.sin(dLat/2) +
        Math.cos(latA * Math.PI/180) * Math.cos(latB * Math.PI/180) * 
        Math.sin(dLon/2) * Math.sin(dLon/2);
    const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
    const d = R * c;

    // 假設縮放比例 scale
    const scale = 30000000*magnification/d;  // 依距離調整，可自行測試調整

    const centerLat = (latA + latB) / 2;
    const centerLon = (lonA + lonB) / 2;

    const posA = project(latA, lonA, centerLat, centerLon, scale);
    const posB = project(latB, lonB, centerLat, centerLon, scale);

    // 轉為 canvas 座標，假設畫布中心點為 (canvas.width/2, canvas.height/2)
    const canvasCenterX = canvas.width / 2;
    const canvasCenterY = canvas.height / 2;

    const canvasPosA = {
        x: canvasCenterX + posA.x,
        y: canvasCenterY - posA.y // Y軸反轉，因為緯度高在上方
    };

    const canvasPosB = {
        x: canvasCenterX + posB.x,
        y: canvasCenterY - posB.y
    };

    // 清空畫布
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.font = "24px Arial";

    // 畫點A
    ctx.fillStyle = "#ff9800";
    ctx.beginPath();
    ctx.arc(canvasPosA.x, canvasPosA.y, 10*magnification, 0, 2 * Math.PI);
    ctx.fill();
    ctx.fillText("GND", canvasPosA.x + 15*magnification, canvasPosA.y - 5*magnification);

    // 畫點B
    ctx.fillStyle = "#2196f3";
    ctx.beginPath();
    ctx.arc(canvasPosB.x, canvasPosB.y, 10*magnification, 0, 2 * Math.PI);
    ctx.fill();
    ctx.fillText("Rocket", canvasPosB.x + 15*magnification, canvasPosB.y - 5*magnification);

    const el = document.getElementById("gps-distance");
    if (el) {
        el.textContent = `距離約 ${d.toFixed(1)} 公尺`;
    }
}


export function resizeCanvasToDisplaySize() {
    // 取得 CSS 尺寸
    const width = canvas.clientWidth;
    const height = canvas.clientHeight;
    
    // 檢查是否與當前 canvas 尺寸不符，避免不必要重設
    if (canvas.width !== width || canvas.height !== height) {
        canvas.width = width*magnification;
        canvas.height = height*magnification;
        return true;  // 表示尺寸有變，畫布需要重繪
    }
    return false;  // 無變動
}

function project(lat, lon, centerLat, centerLon, scale) {
    // 將經緯度轉成 x,y 相對位置，簡單以經度差作 X，緯度差作 Y，並乘以縮放比例 scale

    const x = (lon - centerLon) * scale;
    const y = (lat - centerLat) * scale;

    return { x, y };
}