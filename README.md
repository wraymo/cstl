# cstl
A C implementation of C++ STL
<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}
.tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}
.tg .tg-c3ow{border-color:inherit;text-align:center;vertical-align:top}
</style>
<table class="tg">
  <tr>
    <th class="tg-c3ow">﻿number of operations</th>
    <th class="tg-c3ow">type</th>
    <th class="tg-c3ow">insertion time (ms)</th>
    <th class="tg-c3ow">search time (ms)</th>
    <th class="tg-c3ow">deletion time (ms)</th>
  </tr>
  <tr>
    <td class="tg-c3ow" rowspan="2">100000</td>
    <td class="tg-c3ow">C++ STL</td>
    <td class="tg-c3ow">227</td>
    <td class="tg-c3ow">146</td>
    <td class="tg-c3ow">484</td>
  </tr>
  <tr>
    <td class="tg-c3ow">cstl</td>
    <td class="tg-c3ow">173</td>
    <td class="tg-c3ow">108</td>
    <td class="tg-c3ow">136</td>
  </tr>
  <tr>
    <td class="tg-c3ow" rowspan="2">500000</td>
    <td class="tg-c3ow">C++ STL</td>
    <td class="tg-c3ow">1059</td>
    <td class="tg-c3ow">725</td>
    <td class="tg-c3ow">2395</td>
  </tr>
  <tr>
    <td class="tg-c3ow">cstl</td>
    <td class="tg-c3ow">1132</td>
    <td class="tg-c3ow">825</td>
    <td class="tg-c3ow">951</td>
  </tr>
  <tr>
    <td class="tg-c3ow" rowspan="2">1000000</td>
    <td class="tg-c3ow">C++ STL</td>
    <td class="tg-c3ow">2130</td>
    <td class="tg-c3ow">1448</td>
    <td class="tg-c3ow">4782</td>
  </tr>
  <tr>
    <td class="tg-c3ow">cstl</td>
    <td class="tg-c3ow">2539</td>
    <td class="tg-c3ow">1827</td>
    <td class="tg-c3ow">2173</td>
  </tr>
  <tr>
    <td class="tg-c3ow" rowspan="2">5000000</td>
    <td class="tg-c3ow">C++ STL</td>
    <td class="tg-c3ow">10577</td>
    <td class="tg-c3ow">7229</td>
    <td class="tg-c3ow">24130</td>
  </tr>
  <tr>
    <td class="tg-c3ow">cstl</td>
    <td class="tg-c3ow">16341</td>
    <td class="tg-c3ow">12872</td>
    <td class="tg-c3ow">15140</td>
  </tr>
</table>

