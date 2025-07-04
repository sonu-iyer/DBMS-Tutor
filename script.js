// Function to load content based on the sidebar click
function loadContent(page) {
    let contentArea = document.getElementById('content-area');
    
    switch(page) {
      case 'home':
        contentArea.innerHTML = `
          <h1>Welcome to the SQL Dashboard</h1>
          <p>This is your home page.</p>
        `;
        break;
      case 'intro':
        contentArea.innerHTML = `
          <h1>Run SQL Queries</h1>
          <p>Here you can execute your SQL queries.</p>
          <textarea rows="10" cols="50"></textarea>
          <button>Execute</button>
        `;
        break;
      case 'syntax':
        contentArea.innerHTML = `
          <h1>View Tables</h1>
          <p>Here is a list of all available tables in your database:</p>
          <ul>
            <li>users</li>
            <li>products</li>
            <li>orders</li>
          </ul>
        `;
        break;
      case 'select':
        contentArea.innerHTML = `
          <h1>Settings</h1>
          <p>Adjust your database settings here.</p>
        `;
        break;
      default:
        contentArea.innerHTML = `
          <h1>Page Not Found</h1>
          <p>The page you requested does not exist.</p>
        `;
    }
  }