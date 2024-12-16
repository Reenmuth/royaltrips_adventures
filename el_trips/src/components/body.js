import React from 'react';
import Slider from 'react-slick';
import './homepage.css';
import 'slick-carousel/slick/slick.css';
import 'slick-carousel/slick/slick-theme.css';

const Homepage = () => {
  // Slider settings for the moving images
  const sliderSettings = {
    dots: true,
    infinite: true,
    speed: 1000,
    slidesToShow: 1,
    slidesToScroll: 1,
    autoplay: true,
    autoplaySpeed: 3000,
  };

  return (
    <div className="homepage">
      {/* Services Section */}
      <section className="services">
        <h2>Our Services</h2>
        <div className="service-list">
          <div className="service-item">
            <h3>Team Building</h3>
            <p>We organize team-building events to strengthen team bonds.</p>
          </div>
          <div className="service-item">
            <h3>Hiking Trips</h3>
            <p>Enjoy adventurous hiking trips in breathtaking locations.</p>
          </div>
          <div className="service-item">
            <h3>Customized Tours</h3>
            <p>We offer personalized tour packages for families and groups.</p>
          </div>
        </div>
      </section>

      {/* Moving Images Section */}
      <section className="carousel">
        <h2>Our Past Events & Trips</h2>
        <Slider {...sliderSettings}>
          <div>
            <img
              src="/images/pic3.jpeg"
              alt=""
            />
          </div>
          <div>
            <img
              src="/images/pic1.jpeg"
              alt="Event 2"
            />
          </div>
          <div>
            <img
              src="/images/pic2.jpeg"
              alt="Trip 1"
            />
          </div>
        </Slider>
      </section>

      

      {/* Payment Section */}
      <section className="payment">
        <h2>Secure Your Trip</h2>
        <p>Pay now to secure your spot for the next adventure!</p>
        <button className="payment-btn">Make a Payment</button>
      </section>
    </div>
  );
};

export default Homepage;
