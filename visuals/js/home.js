// displays the correct state selected
function img_state_display() {
    // get the user's month, year, and state selection
    var month = document.getElementById("month").value;
    var year = document.getElementById("year").value;
    var state_name = document.getElementById("state").value;


    document.getElementById("image_section").style.backgroundImage = "url(img/" + state_name + ".png)";

    if (state_name.includes("_"))
    {
        state_name = state_name.replace("_", " ");
    }

    document.getElementById("hot_words").innerText =  "Top 10 Hotspots for " + state_name + " in " + month + " " + year;
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


// get the data from our file based on the date only
function get_data_date() {

    // reset the state selection
    img_state_reset();

    // get the user's month and year selection
    var month = document.getElementById("month").value;
    var year = document.getElementById("year").value;

    // update the hotspot words
    document.getElementById("hot_words").innerText = "Top 10 Hotspots for " + month + " " + year;


    // collect the placeholders for our file to write over
    var first = document.getElementById("one").value;
    var second = document.getElementById("two").value;
    var third = document.getElementById("three").value;
    var fourth = document.getElementById("four").value;
    var fifth = document.getElementById("five").value;
    var sixth = document.getElementById("six").value;
    var seventh = document.getElementById("seven").value;
    var eighth = document.getElementById("eight").value;
    var ninth = document.getElementById("nine").value;
    var tenth = document.getElementById("ten").value;


    // call whatever function we use to get the data we want


    // replace previous variables with new values


    // display the new data
    show_hot(first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth);
}

// get the data from our file based on the date and filter by state
function get_data_state() {

    // display the selected state
    img_state_display();

    // get the user's month, year, and state selection
    var month = document.getElementById("month").value;
    var year = document.getElementById("year").value;
    var state_name = document.getElementById("state").value;


    // create the placeholders for our file to write over
    var first = document.getElementById("one").value;
    var second = document.getElementById("two").value;
    var third = document.getElementById("three").value;
    var fourth = document.getElementById("four").value;
    var fifth = document.getElementById("five").value;
    var sixth = document.getElementById("six").value;
    var seventh = document.getElementById("seven").value;
    var eighth = document.getElementById("eight").value;
    var ninth = document.getElementById("nine").value;
    var tenth = document.getElementById("ten").value;


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
