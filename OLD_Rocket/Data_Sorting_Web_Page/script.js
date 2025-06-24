const intKeys = ["package_count", "recive_time"];
const floatKeys = ["alt", "ver", "acc"]; // 順序需與 data.f 對應
const boolKeys = [
    "Para 1", "Para 2", "Para 3", "L1 Fail", "L2 Fail", 
    "BMP 1", "BMP 2", "Acc", "Hgyro", "Hfreq Data", "Sky GPS", "Ground GPS"
];

async function fetchData() {
    try {
        const response = await fetch('/data');
        const data = await response.json();

        // 更新 float 資料
        intKeys.forEach((key, index) => {
        const el = document.getElementById(key);
            if (el) el.textContent = data.i[index].toFixed(2);
        });

        // 更新 float 資料
        floatKeys.forEach((key, index) => {
        const el = document.getElementById(key);
            if (el) el.textContent = data.f[index].toFixed(2);
        });

        // 更新 bool 狀態視覺化
        updateBoolList(data.b);

    } catch (error) {
        console.error("Fetch error:", error);
    }
}

function updateBoolList(bools) {
    const container = document.getElementById("bool_data_list");
    container.innerHTML = "";
    bools.forEach((value, index) => {
        const div = document.createElement("div");
        div.className = "bool_item";
        div.innerHTML = `
            <div class="bool_circle ${value ? "bool_on" : "bool_off"}"></div>
            <div class="bool-label">${boolKeys[index] || "Flag" + index}</div>
        `;
        container.appendChild(div);
    });
}

setInterval(fetchData, 1000);
fetchData();

updateBoolList([true, true, true, false, false, true, true, true, true, true, true, true]);