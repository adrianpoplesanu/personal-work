$(document).ready(function () {
    //$('#table_id').DataTable();
    keys = Object.keys(informatii).sort();
    persoane = [];
    for (var i = 0; i < keys.length; i++) {
        persoane.push(informatii[keys[i]]);
    }
    $('#table_id').DataTable({
        "data" : persoane,
        "columns" : [
            { "data" : "contor" },
            { "data" : "cod" },
            { "data" : "numepr" },
            { "data" : "obs" },
            { "data" : "poza" },
            { "data" : "numepoza" },
        ],
        "columnDefs": [{
            "targets": 6,
            "render": function ( data, type, row, meta ) {
                //console.log(row);
                var contor = row['contor'];
                var cod = row['cod'];
                var numepr = row['numepr'];
                var obs = row['obs'];
                var poza = row['poza'];
                var numepoza = row['numepoza'];
                return '<button class="edit-person" data-contor="' + contor + '" data-cod="' + cod + '" data-numepr="' + numepr + '" data-obs="' + obs + '" data-poza="' + poza + '" data-numepoza="' + numepoza + '">Editeaza</button>';
            }
        }]
    });

    $('.edit-person').on('click', function () {
        var contor = $(this).data('contor');
        var cod = $(this).data('cod');
        var numepr = $(this).data('numepr');
        var obs = $(this).data('obs');
        var poza = $(this).data('poza');
        var numepoza = $(this).data('numepoza');
        console.log(contor + ':' + cod + ':' + numepr + ':' + obs + ':' + poza + ':' + numepoza);
    });
});