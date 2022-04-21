import React, { Component } from 'react';

class Logout extends Component {
  state = {
    isLoading: true,
  };

  async componentDidMount() {
    const response = await fetch('/logout');
    //const body = await response.json();
    //const body = await response.text();
    this.setState({ isLoading: false });
    //this.props.history.push('/');
    window.location.href = 'http://localhost:8080';
  };

  render() {
    const isLoading = this.state.isLoading;
    if (isLoading) {
      return <p>Logging you off...</p>;
    }

    return (
      <p>Done!</p>
    );
  }
}

export default Logout;