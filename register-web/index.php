<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>IM注册</title>
    <link rel="stylesheet" type="text/css" href="register.css">
    <script src="https://ajax.aspnetcdn.com/ajax/jquery/jquery-1.9.0.min.js"></script>
    <script>
    $(document).ready(function(){
      $("#show_psw").hide();
      $("#rand").hide();
      $("#get_rand").hide();
    $("#psw").focus(function(){
      $("#show_psw").show();
      $("#rand").hide();
      $("#get_rand").hide();
    });
    $("#psw").focusout(function(){
      $("#show_psw").hide();
    });
    $("#email").focus(function(){
      $("#rand").show();
    });
    $("#email").focus(function(){
      $("#get_rand").show();
    });
    $("#get_rand").click(function(){
      var reg=/[A-z0-9_-]*\@[A-z0-9]+\.[A-z]+/;
      if(!reg.test($("input[id=email]").val()))
      {
          alert("邮箱错误!");
          return;
      }
  
      $.post("regist.php",{em:$("input[id=email]").val()},function(data,status){
			  $("#rand_right").attr("value",data);
        $("#rand_right").css("background-color","#4CAF50");
        var time = 60;
        $("#get_rand").attr("disabled", true);
        var timer = setInterval(function() {
        if (time == 0) {
          clearInterval(timer);
          $("#get_rand").attr("disabled", false);
          $("#get_rand").val("获取验证码");
        } else {
          $('#get_rand').val(time + "秒后重新发送");
          time--;
        }
        }, 1000);
		  });
    });
    $("#sub").click(function(){
      if($("input[id=user]").val() == "")
      {
        alert("请输入用户名!");
        return;
      }
      else if($("input[id=psw]").val() == "")
      {
        alert("请输入密码!");
        return;
      }
      else if($("input[id=email]").val() == "")
      {
        alert("请输入邮箱!");
        return;
      }
      else if($("input[id=rand]").val() == "")
      {
        alert("请输入验证码!");
        return;
      }
      $.post("register.php",{
        user: $("input[id=user]").val(),
        psw: $("input[id=psw]").val(),
        email: $("input[id=email]").val(),
        rand: $("input[id=rand]").val(),
        rand_right: $("input[id=rand_right]").val()
      },function(data,status){
        $("#psw").val("");
        $("#rand").val("");
        alert(data);
      });
    });

    $("#psw").keyup(function(){
      var reg=/^(?!^[0-9]+$)(?!^[A-z]+$)(?!^[^A-z0-9]+$)^[^\s\u4e00-\u9fa5]+$/;
      var reg_space=/^[^\s]+$/;
      var reg_num=/^.{8,16}$/;
      if(!reg_space.test($("input[id=psw]").val()))
      {
        $("#li1").css("color","red");
      }else
      {
        $("#li1").css("color","#cfcfcf");
      }
      if(!reg_num.test($("input[id=psw]").val()))
      {
        $("#li2").css("color","red");
      }else
      {
        $("#li2").css("color","#cfcfcf");
      }
      if(!reg.test($("input[id=psw]").val()))
      {
        $("#li3").css("color","red");
      }else
      {
        $("#li3").css("color","#cfcfcf");
      }
    });
  });
  </script>
  </head>
  <body>
      <div class="register_body">
        <form class="submit_form" action="register.php" method="post">
          <input type="text" id="user" name="user" placeholder="昵称" ><br>
          <input type="password" id="psw" name="psw" placeholder="密码" ><br>
          <div id="show_psw" style="color:red">
            <br>
            <li id="li1">不能包含空格</li>
            <li id="li2">长度为8-16个字符</li>
            <li id="li3">必须包含字母,数字,符号的其中2种</li>
          </div>
          <input type="text" id="email" name="email" placeholder="邮箱" ><br>
          <input type="text" id="rand" name="rand" placeholder="验证码" >
          <input type="button" id="get_rand" value="获取验证码">
          <input type="text" id="rand_right" name="rand_right" style="display:none">
          <input type="button" id="sub" value="Sign up for Us">
          <p><br>通过点击 "Sign up for Us" 表示你已赞同并遵守我们的相关协议内容</p>
        </form>
      </div>
  </body>
</html>
