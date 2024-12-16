// src/Footer.js
import React from 'react';
//import './Footer.css'; // Import the CSS for styling

const Footer = () => {
  return (
    <footer className="footer">
      <div className="footer-content">
        <p>&copy; 2024 Your Company. All Rights Reserved.</p>
        <div className="footer-links">
          <a href="/about">About</a>
          <a href="/contact">Contact</a>
          <a href="/privacy-policy">Privacy Policy</a>
        </div>
      </div>
    </footer>
  );
};

export default Footer;
