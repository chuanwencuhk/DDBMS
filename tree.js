var maxsite = 4+1;
var node_num = 0;
var node_list = new Array();
var queue = new Array();
var x = new Array(), y = new Array();//存储每个节点画的位置
var root;
var str = ["","∪","⋈","δ","π"]

function node()
{	var fa;
	var child;
	var type;
	var str;
	var dep;
}

function add_node(str)
{	document.write(str+"<br>");
	var num_con = str.split("/");
	//将节点内容加入
	node_num++;
	var num = num_con[0].split(" ");
	node_list[num[0]] = new node();
	node_list[num[0]].str = num_con[1];
	//将其他加入
	node_list[num[0]].type = num[1];
	//if (type=="4") root = node_num;
	node_list[num[0]].fa = num[2];
	node_list[num[0]].child = new Array();
	node_list[num[0]].child[0] = num[3];
	for (var i=1;i<=num[3];i++)
	{	node_list[num[0]].child[i] = num[3+i];	
	}
	node_list[num[0]].dep = num[3+parseInt(num[3])+1];
	document.write("dep:"+node_list[num[0]].dep+"<br>");
}

function max(a,b)
{	if (a>b) return a;
	else return b; 
}

function get_depth(i)
{	var m = 0;
	if (node_list[i].child[0]>0) 
	{	for (var j=1;j<=node_list[i].child[0];j++)
		{	m = max(m, get_depth(node_list[i].child[j])+1);
		}
		return m;
	}
	else return 1; 
}

function get_fa(i)
{	if (node_list[i].fa!=-1)	return get_fa(node_list[i].fa);
	else	return i; 
}


function draw_tree(ren,colors)
{	root = get_fa(1);
	var depth = get_depth(root);
	var width = 800, height = 600, ow = 20, oh =30;
	var dh = (height - oh*2)/depth;
	var dw;
	
	var sth = oh+dh/2,stw;
	var l=1,r=1,curdep=1,st=1,en=1;
	queue[l] = root;
	document.write(queue[l]+"<br>");
	
	
	//广度优先遍历树，画出图像
	while (l<=r)
	{	dw = (width-2*ow)/(en-st+1);
		stw = ow + dw/2;
		for (var i=st;i<=en;i++)
		{	var cur = queue[i];
			for (var j=1;j<=node_list[cur].child[0];j++)
			{	r++; 
				queue[r] = node_list[cur].child[j];
			}
			//将节点画在stw,sth处
			document.write(cur+"画在:"+stw+" "+sth+"<br>");
			ren.label(str[node_list[cur].type]+" "+node_list[cur].str, stw -(str[node_list[cur].type].length+node_list[cur].str.length+1)*3.3, sth-8)//横坐标减去文本长度的一半(估计) 纵坐标-8
	            .attr({
	            r: 5,
	            fill: colors[1]
	        })  
	        	.css({
                color: 'white',
                fontWeight: 'bold',
                align: 'center'
            })
                .add();
			x[cur] = stw; y[cur]=sth;
			//如果有父节点，画一条与父节点连接的直线
			var fa = node_list[cur].fa;
			if (fa!=-1)
			{	document.write(stw+" "+sth+"连接:"+x[fa]+" "+y[fa]+"<br>");
				ren.path(['M', stw, sth-16, 'L', x[fa], y[fa]+20])
		            .attr({
		            'stroke-width': 2,
		            stroke: 'silver',
		            dashstyle: 'dash'
		        })
		           .add();
			}

			
			//更新stw
			stw += dw;
		}
		//处理下一层，更新sth,st,en
		curdep++;
		st = en + 1; en = st;
		while ((en+1<=r) && (node_list[queue[en+1]].dep==curdep))
		{	en++;
		}
		sth += dh;
		l=st;
	}
	
//	$(function () {
//	    $('#container').highcharts({
//	        chart: {
//	            backgroundColor: 'white',
//	            events: {
//	                load: function () {
//	                    // Draw the flow chart
//	                    var ren = this.renderer,
//	                        colors = Highcharts.getOptions().colors,
//	                        rightArrow = ['M', 0, 0, 'L', 100, 0, 'L', 95, 5, 'M', 100, 0, 'L', 95, -5],
//	                        leftArrow = ['M', 100, 0, 'L', 0, 0, 'L', 5, 5, 'M', 0, 0, 'L', 5, -5];
//	                    // Separator, client from service
//	                    ren.path(['M', 120, 40, 'L', 120, 330])
//	                        .attr({
//	                        'stroke-width': 2,
//	                        stroke: 'silver',
//	                        dashstyle: 'dash'
//	                    })
//	                        .add();
//	                    // Separator, CLI from service
//	                    ren.path(['M', 420, 40, 'L', 420, 330])
//	                        .attr({
//	                        'stroke-width': 2,
//	                        stroke: 'silver',
//	                        dashstyle: 'dash'
//	                    })
//	                        .add();
//	                    // Headers
//	                    ren.label('Web 客户端', 20, 40)
//	                        .css({
//	                        fontWeight: 'bold'
//	                    })
//	                        .add();
//	                }
//	            }
//	        },
//	        title: {
//	            text: 'Highcharts导出服务器概述',
//	            style: {
//	                color: 'black'
//	            }
//	        }
//	    });
//	});
}

