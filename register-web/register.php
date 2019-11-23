<?php
$output=exec('./mysql/exe find '.$_POST['email']);
$rand = $_POST['rand'];
$rand_right = $_POST['rand_right'];
$user_name = $_POST['user'];
$user_pass = $_POST['psw'];
$user_email = $_POST['email'];
if($output == "已存在!")
{
    echo '邮箱已存在!';
}else
{
    global $rand,$rand_right;
    if($rand != $rand_right)
    {
        echo '验证码错误!';
    }
    else
    {
        if($rand != "")
        {
            global $user_name,$user_pass,$user_email;
            $result=exec('./mysql/exe add '.$user_name .' ' .$user_pass .' ' .$user_email);
            if($result == "注册成功!")
            {
                echo '注册成功!';
            }else
            {
                echo '注册失败!';
            }
        }else
        {
            echo "请输入验证码!";
        }
    }
}
?>
