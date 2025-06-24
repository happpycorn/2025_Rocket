export function updateValue(id, value) {
    const el = document.getElementById(id);
    if (el) el.innerText = value;
}

function formatSigned(value, decimals = 2) {
    const number = parseFloat(value);
    if (isNaN(number)) return "--";
    const fixed = number.toFixed(decimals);
    return number >= 0 ? `+${fixed}` : fixed;
}

export function updateTelemetryValues(data) {
    let lastSlope = null;
    if (data.slope_data && data.slope_data.length > 0) {
        lastSlope = data.slope_data[data.slope_data.length - 1];
    }

    updateValue("alt_max", formatSigned(data.max_alt));
    updateValue("alt_now", lastSlope ? formatSigned(lastSlope[1]) : "--");
    updateValue("ver", lastSlope ? formatSigned(lastSlope[2]) : "--");
    updateValue("acc", lastSlope ? formatSigned(lastSlope[3]) : "--");

    updateValue("runtime", (data.time / 1000).toFixed(2));
    updateValue("packet_index", data.recive_pack_count ?? "--");
    updateValue("receive_time", (data.last_recive_time / 1000).toFixed(2));
    updateValue("pitch", data.attit_data[1].toFixed(2));
}
