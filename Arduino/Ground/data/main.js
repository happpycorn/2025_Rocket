async function fetchData() {
  try {
    const response = await fetch('/data');
    const data = await response.json();

    document.getElementById("floatData").textContent = JSON.stringify(data.f, null, 2);
    document.getElementById("boolData").textContent = JSON.stringify(data.b, null, 2);
    document.getElementById("doubleData").textContent = JSON.stringify(data.d, null, 2);
  } catch (error) {
    document.getElementById("floatData").textContent = "Failed to load data.";
    document.getElementById("boolData").textContent = "Failed to load data.";
    document.getElementById("doubleData").textContent = "Failed to load data.";
    console.error("Fetch error:", error);
  }
}

setInterval(fetchData, 1000); // 每秒更新一次
fetchData(); // 初始化時先抓一次
