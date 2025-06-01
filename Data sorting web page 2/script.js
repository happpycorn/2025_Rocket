const { createApp, ref, onMounted } = Vue;

createApp({
setup() {
    const statusList = ref([]);
    const locations = ref([]);
    const warningMessage = ref("Loading...");
    let map = null;
    let markers = [];

    function evaluateWarning(data) {
        const errors = [];

        data.forEach(item => {
            const label = item.label.toLowerCase();
            if (label.includes("condition") && item.value !== "ok") {
                errors.push(`${item.label} is abnormal`);
            }
            if (label === "vertical acceleration" && Math.abs(item.value) > 20) {
                errors.push("Acceleration too high");
            }
            if (label === "lora-delayed time" && item.value > 5) {
                errors.push("Lora delay too long");
            }
        });

        return errors.length > 0
            ? "⚠ Warning:\n" + errors.join("\n")
            : "All seems to be normal!\nAnd I’ll keep hoping so...";
    }

    async function loadData() {
    try {
        const [statusRes, locRes] = await Promise.all([
            fetch("./data/status.json"),
            fetch("./data/locations.json")
        ]);

        const statusData = await statusRes.json();
        const locationData = await locRes.json();

        statusList.value = statusData;
        warningMessage.value = evaluateWarning(statusData);

        // 更新地圖
        if (!map) {
        map = L.map("map").setView(locationData[0], 16);
        L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
            attribution: "&copy; OpenStreetMap contributors"
        }).addTo(map);
        }

        // 清除舊的 marker
        markers.forEach(m => map.removeLayer(m));
        markers = locationData.map(coord => L.marker(coord).addTo(map));
    } catch (err) {
        warningMessage.value = "🚨 Error loading data!";
        console.error(err);
    }
    }

    onMounted(() => {
    loadData(); // 初次載入
    setInterval(loadData, 5000); // 每 5 秒重載
    });

    return { statusList, warningMessage };
}
}).mount("#app");