#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May 19 12:43:37 2023

@author: jhameltb
"""

import subprocess 
fecha = subprocess.getoutput("date")
tiempo = subprocess.getoutput("uptime")
cpu = subprocess.getoutput("lscpu -e")
memoria = subprocess.getoutput("vmstat -s")
disco_duro = subprocess.getoutput("df -h --output=source,fstype,size,used,avail,pcent,target -x tmpfs -x devtmpfs")
html = """ 
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Información del sistema</title>
</head>
<body>

    <h1>Información del sistema</h1>
        <div>
            <table>
                <thead style="background-color:#A1A1A1;color:#FFFFFF">
                </thead>
                <tbody>    
                    <tr>
                        <td>Fecha:</td>
                        <td>""" + fecha + """</td>
                    </tr>  
                    <tr>
                        <td>Hora de inicio:</td>
                        <td>""" + tiempo + """</td>
                    </tr> 
                    <tr>
                        <td>Número de CPU's:</td>
                        <td>""" + str(int(len(cpu)/69 -1)) + """</td>
                    </tr>  
                    <tr>
                        <td>Memoria total:</td>
                        <td>""" + str(float(memoria[5:13])/1000000) + """ GB</td>
                    </tr>
                    <tr>
                        <td>Memoria usada:</td>
                        <td>""" + str(float(memoria[34:42])/1000000) + """ GB</td>
                    </tr>
                    <tr>
                        <td>Memoria libre:</td>
                        <td>""" + str(float(memoria[62:70])/1000000) + """ GB</td>
                    </tr>
                    <tr>
                        <td>Información de discos duros:</td>
                        <td>""" + disco_duro + """ GB</td>
                    </tr>
                </tbody>
            </table>
        </div>

</body>
</html>
"""
print(html)
# print("\n")


# print("TIEMPO DE INICIADO: \n", tiempo)
# print("\n")

# cpu = subprocess.getoutput("lscpu -e")
# print("NÚMERO DE CPU's: \n", cpu)
# print("\n")

# memoria = subprocess.getoutput("free -w")
# print("MEMORIA TOTAL, USADA Y LIBRE: \n", memoria)
# print("\n")

# discos = subprocess.getoutput("df -h")
# print("INFORMACIÓN DISCO DURO: \n", discos)

