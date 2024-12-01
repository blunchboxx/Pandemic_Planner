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

    // call whatever function we use to get the data we want


    // replace previous variables with new values


    // display the new data
    show_hot(first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth);
}


// show the new hotspots
function show_hot(first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth) {


    // fill in the list with our values
    document.getElementById("one").innerText = "I am a fresh hospital name!";
    document.getElementById("two").innerText = second;
    document.getElementById("three").innerText = third;
    document.getElementById("four").innerText = fourth ;
    document.getElementById("five").innerText = fifth;
    document.getElementById("six").innerText = sixth;
    document.getElementById("seven").innerText = seventh;
    document.getElementById("eight").innerText = eighth;
    document.getElementById("nine").innerText = ninth;
    document.getElementById("ten").innerText = tenth;


    // un hide the list
    document.querySelector('#hot_holder').style.display = 'block';
}
