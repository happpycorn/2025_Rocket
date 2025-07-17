const canvas = document.getElementById("pitchCanvas");
const ctx = canvas.getContext("2d");

const magnification = 2;  // 用來控制畫面大小細節（可自行調整）

// 動態調整 canvas 解析度（和 GPS 模組一致）
export function resizePitchCanvas() {
    const width = canvas.clientWidth;
    const height = canvas.clientHeight;

    if (canvas.width !== width * magnification || canvas.height !== height * magnification) {
        canvas.width = width * magnification;
        canvas.height = height * magnification;
        ctx.scale(magnification, magnification);  // 縮放繪圖比例
        return true;
    }
    return false;
}

const rocketImg = new Image();
rocketImg.src = "asset/rocket.png";

export function drawPitch(pitch) {
    const centerX = canvas.width / 2 / magnification;
    const centerY = canvas.height / 2 / magnification;

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    rocketImg.onload = () => {
        draw();
    };

    if (rocketImg.complete) {
        draw(); // 如果圖片已經載入
    }

    function draw() {
        ctx.save();
        ctx.translate(centerX, centerY);
        ctx.rotate((pitch) * Math.PI / 180);
        const scale = 0.1;
        ctx.drawImage(
            rocketImg,
            -rocketImg.width * scale / 2,
            -rocketImg.height * scale / 2,
            rocketImg.width * scale,
            rocketImg.height * scale
        );
        ctx.restore();
    }
}
