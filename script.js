const apiUrl = "http://localhost:3000";

// Show/hide forms
function showAddProductForm() {
    document.getElementById('addProductForm').style.display = 'block';
    document.getElementById('salesForm').style.display = 'none';
    document.getElementById('inventoryTable').style.display = 'none';
}

function showSalesForm() {
    document.getElementById('salesForm').style.display = 'block';
    document.getElementById('addProductForm').style.display = 'none';
    document.getElementById('inventoryTable').style.display = 'none';
}

function showInventory() {
    document.getElementById('inventoryTable').style.display = 'block';
    document.getElementById('addProductForm').style.display = 'none';
    document.getElementById('salesForm').style.display = 'none';
    fetchInventory();
}

// Fetch the inventory and display it
function fetchInventory() {
    fetch(`${apiUrl}/inventory`)
        .then(response => response.json())
        .then(data => {
            const inventoryList = document.getElementById('inventoryList');
            inventoryList.innerHTML = "";
            data.forEach(item => {
                const row = document.createElement('tr');
                row.innerHTML = `
                    <td>${item.name}</td>
                    <td>${item.price}</td>
                    <td>${item.quantity}</td>
                `;
                inventoryList.appendChild(row);
            });
        })
        .catch(error => console.error('Error fetching inventory:', error));
}

// Add a new product
function addProduct() {
    const name = document.getElementById('productName').value;
    const price = document.getElementById('productPrice').value;
    const quantity = document.getElementById('productQuantity').value;

    const product = { name, price, quantity };

    fetch(`${apiUrl}/add-product`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(product)
    })
    .then(response => response.json())
    .then(data => {
        alert('Product added successfully!');
        showInventory();
    })
    .catch(error => console.error('Error adding product:', error));
}

// Make a sale
function makeSale() {
    const productName = document.getElementById('saleProductName').value;
    const quantity = document.getElementById('saleQuantity').value;

    const sale = { productName, quantity };

    fetch(`${apiUrl}/make-sale`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(sale)
    })
    .then(response => response.json())
    .then(data => {
        alert('Sale made successfully!');
        showInventory();
    })
    .catch(error => console.error('Error making sale:', error));
}
