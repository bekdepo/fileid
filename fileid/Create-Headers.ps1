$dt = [DateTime]::Now
$header = @"
// magic.h
// Generated on: $dt

#pragma once
#include <string>
#include "common.hpp"


"@ 


$list = "std::vector<common::MagicInfo> list = {" + [Environment]::NewLine

([xml](gc .\data.xml -raw)).Items.item | % {
   $magic = $_."#text".Split(',')

   $name = $_.shortname
   $offset = if ($_.offset -ne $null) { $_.offset } else { 0 }
   $extra =   if ($_.extra -ne $null) { '"' + $_.extra + '"'} else { "NULL" }

   $header += "unsigned char magic_" + $name + "[" + $magic.Count + "] = {" + $_.'#text' + "};" +[Environment]::NewLine
   $list += '  {"'+ $_.extension +'", "'+ $_.name +'", "' + $_.version + '", '+ $offset +', ' + $magic.Count +', magic_' + $name +', '+ $extra +'},' + [Environment]::NewLine

}
$list += "};"

$outFile = ".\magic.h"
$header | Set-Content $outFile
$list | Add-Content $outFile