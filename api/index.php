<?php 
    // This is the main of the api systeme for my API SMS

    // Access Control
    header('Access-Control-Allow-Origin: *');
    header("Access-Control-Allow-Credentials: true");
    header('Access-Control-Allow-Methods: GET, POST');
    header('Access-Control-Max-Age: 1000');
    header('Access-Control-Allow-Headers: Content-Type, Content-Range, Content-Disposition, Content-Description');
    // Cache control
    header("Cache-Control: no-store, no-cache, must-revalidate"); 
    header("Cache-Control: post-check=0, pre-check=0", false); 
    header("Cache-Control: private");
    header("Pragma: no-cache");
    header('Content-Type:application/json; Charset=UTF-8');

    require('functions.php');

    $result = array();
    $valid_message = false;
    $valid_number = false;
    if(isset($_REQUEST['key'])){

        if(isset($_REQUEST['message'])){
            if(sizeof($_REQUEST['message']) < 100 && sizeof($_REQUEST['message']) > 3){
                $valid_message = true;
            }else{
                $result['status'] = 'error';
                $result['reason'] = 'Error with the message size (<100 and >3)';
            }
        }else{
            $result['status'] = 'error';
            $result['reason'] = 'message parameter not found.';
        }

        if(isset($_REQUEST['number'])){
            if(sizeof($_REQUEST['number']) > 8 && sizeof($_REQUEST['number']) < 15){
                $valid_number = true;
            }else{
                $result['status'] = 'error';
                $result['reason'] = 'Error with the number size (<15 and >8)';
            }
        }else{
            $result['status'] = 'error';
            $result['reason'] = 'number parameter not found.';
        }

        if($valid_message && $valid_number){
            if(!api_CheckIfLineExistInFile('done.txt', $_REQUEST['number']."|".$_REQUEST['message'])){

                if(!api_CheckIfLineExistInFile('waiting.txt', $_REQUEST['number']."|".$_REQUEST['message'])){
                    api_writeFile("waiting.txt", $_REQUEST['number']."|".$_REQUEST['message']);
                    $result['status'] = 'success';
                    $result['reason'] = 'Your message request has been save by the api and will be threat in few seconds.';
                }else{
                    $result['status'] = 'success';
                    $result['reason'] = 'Your message request is Pending please wait...';
                }

            }else{
                $result['status'] = 'success';
                $result['reason'] = 'message sent successfully.';
            }
        }

    }else{
        $result['status'] = 'error';
        $result['reason'] = 'key not found.';
    }

    echo json_encode($result);
?>