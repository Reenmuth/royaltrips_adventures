import React from 'react';
import './header.css';

const Header = () => {
  return (
    <header className="header">
      <div className="header-content">
        <h1 className="title">Royal Trips Adventure</h1>
        <nav className="navbar">
          <ul className="nav-list">
            <li className="nav-item"><a href="#home">Home</a></li>
            <li className="nav-item"><a href="#about">About Us</a></li>
            <li className="nav-item"><a href="#services">Services</a></li>
            <li className="nav-item"><a href="#events">Events</a></li>
            <li className="nav-item"><a href="#contact">Contact</a></li>
          </ul>
        </nav>
      </div>
    </header>
  );
};

export default Header;
