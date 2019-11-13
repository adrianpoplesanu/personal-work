function Persoana(nume, prenume, varsta) {
    this.nume = nume;
    this.prenume = prenume;
    this.varsta = varsta
}

Persoana.prototype.calculeazaVarsta = function () {
    console.log(this.varsta * 10);
}

var persoane = [];

persoane.push(new Persoana("Andrei1<br>", "Vlad<br>", 1));
persoane.push(new Persoana("Adi<br>", "Vlad<br>", 2));
persoane.push(new Persoana("Andrei3<br>", "Vlad<br>", 3));
persoane.push(new Persoana("Andrei1<br>", "Vlad<br>", 4));
persoane.push(new Persoana("Andrei2<br>", "Vlad<br>", 5));
persoane.push(new Persoana("Ramona<br>", "Vlad<br>", 6));
persoane.push(new Persoana("Andrei1<br>", "Vlad<br>", 7));
persoane.push(new Persoana("Andrei2<br>", "Vlad<br>", 8));
persoane.push(new Persoana("Andrei3<br>", "Vlad<br>", 9));

for (var i = 0; i < persoane.length; i++) {
    console.log(persoane[i].nume + persoane[i].nume);
    //persoane[i].calculeazaVarsta();
}