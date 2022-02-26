import React from "react";
import styled from "styled-components";
import { Send } from "@material-ui/icons";
import { useState } from "react";
import axios from "axios";

const Container = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  overflow-y: hidden;
`;

const MessageBox = styled.input`
  type: "text";
  name: "msg";
  width: 90%;
  height: 30px;
  position: absolute;
  bottom: 10px;
  border: 1px solid;
  border-radius: 15px;
  font-size: 18;
`;

const Button = styled.button`
  height: 35px;
  width: 35px;
  position: absolute;
  bottom: 10px;
  right: 65px;
  border-radius: 100%;
  cursor: pointer;
  background-color: #361500;
  color: white;
  display: flex;
  align-items: center;
  justify-content: center;
`;
const Conversation = styled.div`
  display: flex;
  width: 100%;
  height: 85vh;
  flex-direction: column;
  overflow: scroll;
  overflow-x: hidden;
`;
const CbMsg = styled.div`
  font-family: cursive;
  font-size: 20px;
  align-self: flex-start;
  display: block;
  width: 400px;
  margin-left: 70px;
  border-radius: 25px;
  background-color: white;
  padding: 20px;
  text-align: center;
  flexwrap: wrap;
`;
const UsMsg = styled.div`
  font-family: cursive;
  font-size: 20px;
  align-self: flex-end;
  display: block;
  width: 400px;
  margin-right: 70px;
  border-radius: 25px;
  background-color: black;
  color: white;
  padding: 20px;
  text-align: center;
  flexwrap: wrap;
`;

const Message = () => {
  const [msg, setMsg] = useState("");
  const [chat, setChat] = useState([]);
  const handleChange = (e) => {
    console.log(e.target.value);
    setMsg({ msg: e.target.value });
  };
  const handleSend = () => {
    if (msg["msg"] !== "") {
      console.log(msg["msg"]);
      axios
        .post("http://127.0.0.1:5000/user", { msg: msg["msg"] })
        .then((res) => {
          setChat((arr) => [
            ...arr,
            {
              from: "our",
              msag: msg["msg"],
            },
          ]);
          setChat((arr) => [
            ...arr,
            {
              from: "cb",
              msag: res.data,
            },
          ]);

          let interval = window.setInterval(function () {
            var elem = document.getElementById("chat");
            elem.scrollTop = elem.offsetHeight;
            window.clearInterval(interval);
          }, 1000);
        })
        .catch((err) => {
          console.log(err);
        });
    }
  };

  const handleKeypress = (e) => {
    if (e.key === "Enter") {
      handleSend();
    }
  };

  return (
    <Container>
      <Conversation id="chat">
        {chat.map(
          (mg) =>
            (mg.from === "cb" && <CbMsg>{mg.msag}</CbMsg>) ||
            (mg.from === "our" && <UsMsg>{mg.msag}</UsMsg>)
        )}
      </Conversation>
      <MessageBox
        id="inp"
        onChange={(e) => handleChange(e)}
        onKeyPress={(e) => handleKeypress(e)}
        value={msg.value}
      />
      <Button onClick={() => handleSend()}>
        <Send />
      </Button>
    </Container>
  );
};

export default Message;
