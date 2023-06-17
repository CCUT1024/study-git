import thirdparty.A_Calaulator;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Main {
    public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException, NoSuchMethodException, InvocationTargetException, NoSuchFieldException {
        //加载类的写法：后面引号写类的路径,即该类顶部package后的内容.类名
        Class<?> cls = Class.forName("thirdparty.A_Calaulator");
        //生成这个类的实例
        Object o = cls.newInstance();
        //newInstance()调用的是类的无参构造函数，若该类没有无参构造函数，可能执行不了
        //通过无参构造函数得到类的实例

        //调用类里面的某个方法，若不是反射，直接o.add(3,4)就可以了
        //而反射调用了一些API来实现调用方法
        Method method = cls.getMethod("add", int.class, int.class);//得到类中的方法
        //参数分别是要获取类中方法的名称（字符串），方法的参数类型.class
        System.out.println(method.invoke(o,1,2));//通过invoke()执行类中的方法，第一个参数是Object类的变量名
        //其后的是被调用的类中该方法的参数

        //调用无参方法
        Method method1 = cls.getMethod("greet");
        System.out.println(method1.invoke(o));

        //接下来演示的API是动态地修改类其中的某个变量（以name为例）
        String Fieldname = "name";//将name设置为一个变量，令其可以更改
        //之前的写法:o.name是写死的
        Field field = cls.getField(Fieldname);
        //操纵一个变量：给它赋值或获取它的值

        //赋值：set()，某个实例的某个方法
        field.set(o,"My Calculator");//参数分别为：实例，该实例中创建的域(field)中的值要修改成的值

        //获取变量值：get()方法
        System.out.println(field.get(o));//参数分别为：想要获取值对应的实例名

        //以下演示调用有参构造函数
        Constructor<?> constructor = cls.getConstructor(String.class);//获取这个类的构造方法
        //参数分别为：想获得的构造函数的参数类型.class

        //生成一个新的实例：
        Object newObject = constructor.newInstance("New Calculator");
        System.out.println(newObject);

        //正常写法
        /*
        A_Calaulator o = new A_Calaulator();
        System.out.println(o.add(1,2));
        o.name = "My Calculator";
        System.out.println(o.name);
        A_Calaulator newObject = new A_Calaulator("New Calculator");
        System.out.println(newObject);
        */
    }
}

