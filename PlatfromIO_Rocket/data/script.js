const boolKeys = [
    "Para 1", "Para 2", "Para 3", "L1 Fail", "L2 Fail", 
    "BMP 1", "BMP 2", "Acc", "Hgyro", "Hfreq Data", "Sky GPS", "Ground GPS"
];

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

// updateBoolList([true, true, true, false, false, true, true, true, true, true, true, true]);