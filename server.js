const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();
const port = 3000;

app.use(express.json());

// File to store inventory data
const inventoryFile = path.join(__dirname, 'inventory.json');

// Helper function to read inventory from the file
function readInventory() {
    const rawData = fs.readFileSync(inventoryFile);
    return JSON.parse(rawData);
}

// Helper function to save inventory to the file
function saveInventory(inventory) {
    fs.writeFileSync(inventoryFile, JSON.stringify(inventory, null, 2));
}

// API endpoint to get inventory
app.get('/inventory', (req, res) => {
    const inventory = readInventory();
    res.json(inventory);
});

// API endpoint to add a new product
app.post('/add-product', (req, res) => {
    const inventory = readInventory();
    const newProduct = req.body;

    inventory.push(newProduct);
    saveInventory(inventory);

    res.json({ message: 'Product added successfully!' });
});

// API endpoint to make a sale
app.post('/make-sale', (req, res) => {
    const inventory = readInventory();
    const { productName, quantity } = req.body;

    const product = inventory.find(p => p.name === productName);

    if (product && product.quantity >= quantity) {
        product.quantity -= quantity;
        saveInventory(inventory);
        res.json({ message: 'Sale made successfully!' });
    } else {
        res.status(400).json({ message: 'Product not found or insufficient stock' });
    }
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
