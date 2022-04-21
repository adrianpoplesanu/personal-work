import React, { Component } from 'react';
import logo from './logo.svg';
import './App2.css';

class App2 extends Component {
  state = {
    isLoading: true,
    message: "aaa"
  };

  async componentDidMount() {
    const response = await fetch('/api/status');
    //const body = await response.json();
    const body = await response.text();
    this.setState({ message: body, isLoading: false });
  };

  render() {
    const {message, isLoading} = this.state;

    if (isLoading) {
      return <p>Loading...</p>;
    }

    console.log(message);

    return (
      <div className="App2">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <p>{message}</p>
          <p>
            Edit <code>src/App.js</code> and save to reload.
          </p>
          <a
            className="App-link"
            href="https://reactjs.org"
            target="_blank"
            rel="noopener noreferrer"
          >
            Learn React
          </a>
        </header>
      </div>
    );
  }
}

export default App2;
