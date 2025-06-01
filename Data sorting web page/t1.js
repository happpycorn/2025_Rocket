
  const fileInput = document.getElementById("fileInput");
  const resultDisplay = document.getElementById("result");

  fileInput.addEventListener("change", (event) => {
    const file = event.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = (e) => {
      const text = e.target.result;

      if (file.name.endsWith('.json')) {
        try {
          const jsonData = JSON.parse(text);
          processJSONData(jsonData);
        } catch { 
          resultDisplay.textContent = "Invalid JSON file.";
        }
      } else if (file.name.endsWith('.csv') || file.name.endsWith('.txt')) {
        processCSVData(text);
      } else {
        resultDisplay.textContent = "Unsupported file type.";
      }
    };
    reader.readAsText(file);
  });

  // Make sure resultDisplay is cleared initially
  resultDisplay.textContent = "Awaiting file input...";



function processCSVData(csvText) {
  const lines = csvText.trim().split(/\r?\n/);
  if (lines.length < 2) {
    resultDisplay.textContent = "CSV file must contain header and at least one data row.";
    return;
  }

  const headers = lines[0].split(',');
  // Required columns:
  const requiredCols = ['Time', 'Altitude', 'Vertical_Velocity', 'Acceleration'];
  const indices = {};
  for (const col of requiredCols) {
    const idx = headers.indexOf(col);
    if (idx === -1) {
      resultDisplay.textContent = `Missing required column: ${col}`;
      return;
    }
    indices[col] = idx;
  }

  // Parse all data rows
  const data = lines.slice(1).map(line => {
    const parts = line.split(',');
    return {
      Time: parseFloat(parts[indices['Time']]),
      Altitude: parseFloat(parts[indices['Altitude']]),
      Vertical_Velocity: parseFloat(parts[indices['Vertical_Velocity']]),
      Acceleration: parseFloat(parts[indices['Acceleration']]),
    };
  });

  // Check for valid data
  if (data.length === 0) {
    resultDisplay.textContent = "No data rows found.";
    return;
  }

  // Find highest altitude
  const highestAltitude = Math.max(...data.map(d => d.Altitude));

  // For demonstration, show the first row's values as the "moment"
  const current = data[0];

  displayResults(current, highestAltitude);
}

function processJSONData(jsonData) {
  // Expecting array of objects with keys Time, Altitude, Vertical_Velocity, Acceleration
  if (!Array.isArray(jsonData)) {
    resultDisplay.textContent = "JSON data must be an array of objects.";
    return;
  }

  if (jsonData.length === 0) {
    resultDisplay.textContent = "JSON array is empty.";
    return;
  }

  // Validate presence of required keys in first object
  const requiredKeys = ['Time', 'Altitude', 'Vertical_Velocity', 'Acceleration'];
  for (const key of requiredKeys) {
    if (!(key in jsonData[0])) {
      resultDisplay.textContent = `Missing required key in JSON data: ${key}`;
      return;
    }
  }

  // Filter and parse numeric values
  const data = jsonData.map(item => ({
    Time: Number(item.Time),
    Altitude: Number(item.Altitude),
    Vertical_Velocity: Number(item.Vertical_Velocity),
    Acceleration: Number(item.Acceleration)
  }));

  // Find highest altitude
  const highestAltitude = Math.max(...data.map(d => d.Altitude));

  // Show first row for "moment"
  const current = data[0];

  displayResults(current, highestAltitude);
}

function displayResults(current, highestAltitude) {
  const parachuteStatus = "Parachute condition: Not deployed yet."; // static message for now

  const output = 
`Time: ${current.Time}
Altitude: ${current.Altitude}
Highest Altitude: ${highestAltitude}
Vertical Velocity: ${current.Vertical_Velocity}
Acceleration: ${current.Acceleration}

${parachuteStatus}`;

  resultDisplay.textContent = output;
}
