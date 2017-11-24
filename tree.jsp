<!DOCTYPE html>
<html>
	<head>
		<title>查询树</title>
		<%@ page contentType="text/html; charset=UTF-8"%>
		<%@ page import="java.io.BufferedReader"%>  
		<%@ page import="java.io.FileReader"%>  
		<%@ page import="java.io.File"%>  
		<script src="https://img.hcharts.cn/jquery/jquery-1.8.3.min.js"></script>
		<script src="https://img.hcharts.cn/highcharts/highcharts.js"></script>
		<script src="https://img.hcharts.cn/highcharts/modules/exporting.js"></script>
		<script src="https://img.hcharts.cn/highcharts-plugins/highcharts-zh_CN.js"></script>
		<!--  <script src="http://img.hcharts.cn/highcharts/themes/dark-unica.js"></script>-->
		<script src="tree.js"></script>
	
	</head>
	<body>
		<div id="container" style="width: 800px; height: 600px; margin: 0 auto"></div>
		<script>
		<%    
			String path ="C:\\Users\\harpuia\\Documents\\Visual Studio 2017\\Projects\\query_tree\\query_tree";   // 这边文件目录需改成相对路径  
			File file = new File(path,"tree.txt");  
			FileReader fr = new FileReader(file);  //字符输入流  
			BufferedReader br = new BufferedReader(fr);  //使文件可按行读取并具有缓冲功能  
			StringBuffer str = new StringBuffer();   //strB用来存储jsp.txt文件里的内容  
			String strB = br.readLine();  
			while (strB!=null) {  
				str.append(strB).append("<br>");   //将读取的内容放入strB  
		%>
				add_node("<%=strB %>");
		<%
				strB = br.readLine();  
			}  
			br.close();    //关闭输入流  
		%> 
			$('#container').highcharts({
		        chart: {
		            backgroundColor: 'white',
		            events: {
		                load: function () {
		                	var ren = this.renderer,
		            	    colors = Highcharts.getOptions().colors,
		            	    rightArrow = ['M', 0, 0, 'L', 100, 0, 'L', 95, 5, 'M', 100, 0, 'L', 95, -5],
		            	    leftArrow = ['M', 100, 0, 'L', 0, 0, 'L', 5, 5, 'M', 0, 0, 'L', 5, -5];
							draw_tree(ren,colors);
		                }
		            }
		        },
		        title: {
		            text: '查询树',
		            style: {
		                color: 'black'
		            }
		        }
		    });
		</script>
		
	</body>
</html>