import React from "react";
import styled from "styled-components";
const Container = styled.div`
  background-color: #361500;
  height: 60px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin-bottom: 5px;
`;

const Title = styled.h1`
  color: white;
  font-family: cursive;
  letter-spacing: 5px;
`;

const Header = () => {
  return (
    <Container>
      <Title>ENIGMA</Title>
    </Container>
  );
};

export default Header;
