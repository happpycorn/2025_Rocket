export function updateWarnings(warnings) {
    const list = document.getElementById("warning-list");
    list.innerHTML = "";

    if (!warnings || warnings.length === 0) {
        const item = document.createElement("li");
        item.textContent = "目前無警告訊息";
        item.style.color = "#aaa";
        list.appendChild(item);
        return;
    }

    warnings.forEach(warning => {
        const item = document.createElement("li");
        item.textContent = warning;
        list.appendChild(item);
    });
}
