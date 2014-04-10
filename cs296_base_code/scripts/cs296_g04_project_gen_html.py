import re
import subprocess

tex_file = open("./doc/proj_report.tex", "r")
html_file = open("./doc/cs296_g04_project_report.html", "w")
html_file.write("<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>CS296 Group 04 Project: Simulation of a Radial Engine</title>\n\t<head>\n\n\t<body class=\"body\"style=\"background-image:url(\'./images/grey_wash_wall.png\');font-size:20px;font-family:Verdana;height:100%;width:80%;margin: 0 auto\">\n")
block = ""
p = re.compile(r'\\cite{[a-zA-Z0-9]*}')
indent = -1

for line in tex_file:
	line = p.sub("", line)
	line = line.replace("\\&", "&")
	line = line.replace("\\%", "%")

	if "verbatim" in line and "end" in line:
			block = ""
			html_file.write("\n\t\t</pre>\n")

	if re.match(r'^%', line) or "usepackage" in line or "maketitle" in line or re.match(r'^\\end', line):
		continue

	if re.match(r'^\\title', line):
		title = line[line.find("{") + 1:line.find("}")]
		html_file.write("\t<h1 style=\"text-align:center\">" + title + "</h1>\n")

	if re.match(r'^\\author', line):
		author_list = line[line.find("{") + 1:line.find("}")]
		author_list = author_list.replace("\\\\", "<br>\n")
		html_file.write("\t<div style=\"text-align:right;margin-right:15%\">\n" + author_list +  "\n\t</div>\n")
		html_file.write("\t<hr>")

	if block == "subsection":
		html_file.write("\t<div style=\"margin-left:1.5%\">\n")
		html_file.write(line + "\n\t<br>\n");
		block = ""
		html_file.write("\t</div>\n")

	if block == "section":
		html_file.write("\t<div style=\"margin-left:0.5%\">\n")
		html_file.write(line + "\n\t<br>\n");
		block = ""
		html_file.write("\t</div>\n")

	if block == "ul":
		list_item = line[line.find("item") + 5:].strip()
		html_file.write("\t\t<li>" + list_item + "</li>\n")
		block = ""

	if block == "code":
		html_file.write(line)

	if re.match(r"^\\section", line):
		html_file.write("\t<br>\n\t<h2>" + line[line.find("{") + 1:line.find("}")] + "</h2>\n")
		block = "section"
		indent = 0.5

	if re.match(r"^\\subsection", line):
		html_file.write("\t<h3 style=\"margin-left:1%\">" + line[line.find("{") + 1:line.find("}")] + "</h3>\n")
		block = "subsection"
		indent = 1.5

	if re.match(r'^\\includegraphics', line.strip()):
		image_src = line[line.find("{") + 1:line.find("}")]
		image_src = image_src.replace("g04_plot", "g04_lab09_plot")
		html_file.write("\n\t\t<br>\n\t\t<img src=" + image_src + " width = \"40%\" style=\"display: block;margin-left: auto;margin-right: auto\"> <br>\n")

	if re.match(r'^\\begin{itemize}', line):
		block = "ul"
		html_file.write("\n\t<ul>\n")

	if re.match(r'^\\item', line):
		block = "ul"

	if re.match(r'^\\indent', line):
		line = line[7:]
		html_file.write("\t<div style=\"margin-left:" + str(indent) + "%\">\n")
		html_file.write(line + "\n\t<br>\n");
		block = ""
		html_file.write("\t</div>\n")

	if re.match(r'^\\begin{verbatim}', line):
		block = "code"
		html_file.write("\n\t\t<pre>\n")

bib_file = open("./doc/proj_report.bib", "r")
html_file.write("\n\t<h2>References</h2>\n\t\t<ul>")

for line in bib_file:
	line_array = line.split(",")
	url = line_array[3][line_array[3].find("{") + 1:line_array[3].find("}")]
	title = line_array[2][10:len(line_array[2])-1]
	html_file.write("<li> <a href=\"" + url + "\">" + title + "</a></li>")

html_file.write("")