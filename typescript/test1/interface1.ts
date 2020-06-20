interface Person {
    firstName: string;
    lastName: string;
}

function greeter(person: Person) {
    console.log("salutari");
    console.log(person.firstName);
    console.log(person.lastName);
}

var p = { firstName: "Gogu", lastName: "Gaze"};

greeter(p);
