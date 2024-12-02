//Converts month format to 3 letter format
function getMonthAbbreviation(month) {
    const monthAbbreviations = {
        "January": "Jan",
        "February": "Feb",
        "March": "Mar",
        "April": "Apr",
        "May": "May",
        "June": "Jun",
        "July": "Jul",
        "August": "Aug",
        "September": "Sep",
        "October": "Oct",
        "November": "Nov",
        "December": "Dec"
    };
    return monthAbbreviations[month] || month.substring(0, 3);
}

// displays the correct state selected
function img_state_display(month, year, state_name) {

    // get the picture for the selected state and display it
    document.getElementById("image_section").style.backgroundImage = "url(img/" + state_name + ".png)";

    // account for underscore in state names
    if (state_name.includes("_"))
    {
        state_name = state_name.replace("_", " ");
    }

    // update the heading for the user's selection 
    document.getElementById("hot_words").innerText = "Top 10 Hotspots for " + state_name + " in " + month + " " + year;
}

// resets the state image to the default
function img_state_reset() {
    document.getElementById("image_section").style.backgroundImage = "url(img/fresh_states.png)";

    document.getElementById("hot_words").innerText = "Top 10 Hotspots Will Be Displayed Here";
}

// completely reset the page to default
function complete_reset() {

    // reset the state image
    img_state_reset();

    // reset the variables or hide the list
    document.querySelector('#hot_holder').style.display = 'none';
}

// get the data from our file based on the date and filter by state
function get_data_state() {

    // get the user's selections
    var month = document.getElementById("month").value;
    var year = document.getElementById("year").value;
    var state_name = document.getElementById("state").value;

    // display the selected state based on user's input
    img_state_display(month, year, state_name);

    // create the default valuees for our file to write over
    var first = " [Less than 10 Hospitals Reported] ";
    var second = " [Less than 10 Hospitals Reported] ";
    var third = " [Less than 10 Hospitals Reported] ";
    var fourth = " [Less than 10 Hospitals Reported] ";
    var fifth = " [Less than 10 Hospitals Reported] ";
    var sixth = " [Less than 10 Hospitals Reported] ";
    var seventh = " [Less than 10 Hospitals Reported] ";
    var eighth = " [Less than 10 Hospitals Reported] ";
    var ninth = " [Less than 10 Hospitals Reported] ";
    var tenth = " [Less than 10 Hospitals Reported] ";

    // Fetch data from the API
    let state_code = "";
    switch(state_name) {
        case "Alabama": state_code = "AL"; break;
        case "Florida": state_code = "FL"; break;
        case "Georgia": state_code = "GA"; break;
        case "Mississippi": state_code = "MS"; break;
        case "North Carolina": state_code = "NC"; break;
        case "South Carolina": state_code = "SC"; break;
        case "Tennessee": state_code = "TN"; break;
    }

    let date = getMonthAbbreviation(month) + "-" + year;

    fetch(`/api/hospitals/capacity?state=${state_code}&date=${date}`)
        .then(response => {
            if (!response.ok) {
                throw new Error("Network error!");
            }
            return response.text();
        })
        .then(data => {
            // Split the response into lines
            const hospitals = data.split("\n").filter(line => line.trim() !== "");
        
            // Clear existing table data
            const tbody = document.getElementById("hotspot-data");
            tbody.innerHTML = "";
        
            // Add each hospital to the table
            hospitals.forEach((hospital, index) => {
                const [name, capacity] = hospital.split(": ");
                const row = document.createElement("tr");
                row.innerHTML = `
                    <td>${index + 1}</td>
                    <td>${name}</td>
                    <td>${capacity}</td>
                `;
                tbody.appendChild(row);
            });

            // Show the table
            document.querySelector('#hot_holder').style.display = 'block';
        })
        .catch(error => {
            console.error("Error fetching data:", error);
            alert("Unable to find data for the selected state and date.");
        });

}
