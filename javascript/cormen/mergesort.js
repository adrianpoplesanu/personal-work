var a = [8, 5, 3, 6, 4, 2, 9, 7, 1];

function merge(a, low, mid, high) {
    var i = low, j = mid + 1, k = low, b = [];
    while(i <= mid && j <= high) {
        if (a[i] < a[j]) {
            b.push(a[i++]);
        } else {
            b.push(a[j++]);
        }
    }
    while (i <= mid) b.push(a[i++]);
    while (j <= high) b.push(a[j++]);
    k = 0;
    for (var i = low; i <= high; i++) {
        a[i] = b[k++];
    }
}

function msort(a, low, high) {
    if (low < high) {
        var mid = Math.floor((low + high) / 2);
        msort(a, low, mid);
        msort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

msort(a, 0, 8);
console.log(a);
