<?php 

    function api_CheckIfLineExistInFile($file, $line){
        if( strpos(file_get_contents($file),$line) !== false) {
            return true;
        }else{
            return false;
        }
    }

    function api_readFile($file){
        $myfile = fopen($file, "r") or die("Unable to open file!");
        $result = fread($myfile,filesize($file));
        fclose($myfile);
        return $result;
    }

    function api_writeFile($file, $txt){
        $myfile = fopen($file, "w") or die("Unable to open file!");
        fwrite($myfile, $txt);
        fclose($myfile);
        return true;
    }
?>