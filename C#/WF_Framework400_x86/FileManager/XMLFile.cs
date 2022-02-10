using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace FileManager
{
    public static class XMLFile
    {
        public static bool MSB { get; set; } = true;
        public static string Export(object Obj, string FilePath)
        {
            if (Obj != null)
            {
                PropertyInfo[] propertise = Obj.GetType().GetProperties();
                foreach (PropertyInfo property in propertise)
                {
                    object[] custom_attribute = property.GetCustomAttributes(false);
                    if (custom_attribute != null && custom_attribute.Length > 0)
                    {
                        foreach (object attribute in custom_attribute)
                        {
                            PropertyInfo attribute_property = attribute.GetType().GetProperty("FileRender");
                            if (attribute_property != null)
                            {
                                return property.Name + " = " + property.GetValue(Obj, null);
                            }
                        }
                    }
                }
            }
            return "";
        }
    }
    public class XMLNode
    {
        public string TypeName { get; set; }
        public Dictionary<string, string> Attributes { get; set; } = new Dictionary<string, string>();
        public string this[string AttributeName]
        {
            get
            {
                if (Attributes.ContainsKey(AttributeName))
                    return Attributes[AttributeName];
                return null;
            }
        }
        public string this[int AttributeIndex]
        {
            get
            {
                if (AttributeIndex < 0)
                    return null;
                if (Attributes.Count > AttributeIndex)
                    return Attributes.Values.ElementAt(AttributeIndex);
                return null;
            }
        }
        public XMLNode Parent { get; set; }
        private List<XMLNode> Children { get; set; } = new List<XMLNode>();
        public bool Import(string Text, ref int TextIndex)
        {
            TextIndex++;
            string type_name = "";
            while (Text[TextIndex] != ' ')
                type_name += Text[TextIndex++];
            this.TypeName = type_name;
            return true;
        }
        public string GetText(int BaseLevel = 0)
        {
            string space = "";
            for (int i = 0; i < this.GetLevel() - BaseLevel; i++)
                space += "  ";
            string text = space + "<" + TypeName;
            for (int i = 0; i < Attributes.Count; i++)
                text += " " + Attributes.Keys.ElementAt(i) + "=" + "\"" + Attributes.Values.ElementAt(i) + "\"";
            text += ">";
            if (Children != null && Children.Count > 0)
            {
                text += "\n";
                foreach (XMLNode node in Children)
                    text += space + node.GetText(BaseLevel) + "\n";
            }
            if (Children != null && Children.Count > 0)
                text += space;
            text += "<" + TypeName + "/>";
            return text;
        }
        public int GetLevel()
        {
            int level = 0;
            XMLNode node = Parent;
            while (node != null)
            {
                level++;
                node = node.Parent;
            }
            return level;
        }
        private bool Exist(XMLNode Node)
        {
            if (this == Node)
                return true;
            if (Children != null && Children.Count > 0)
            {
                foreach (XMLNode child in Children)
                {
                    if (child.Exist(Node))
                        return true;
                }
            }
            return false;
        }
        public bool ExistNode(XMLNode Node)
        {
            XMLNode source = this;
            while (source.Parent != null)
                source = source.Parent;
            return source.Exist(Node);
        }
        public bool AddChild(XMLNode Child)
        {
            if (ExistNode(Child))
                return false;
            Children.Add(Child);
            Child.Parent = this;
            return true;
        }
        public bool RemoveChild(XMLNode Child)
        {
            if (Children.Contains(Child))
            {
                Child.Parent = null;
                Children.Remove(Child);
                return true;
            }
            return false;
        }
        public bool RemoveChild(int Index)
        {
            if (Children.Count > Index)
            {
                Children[Index].Parent = null;
                Children.RemoveAt(Index);
                return true;
            }
            return false;
        }
        public void RemoveChildren(string TypeName, string AttributeName = null, string AttributeValue = null)
        {
            List<XMLNode> children = GetChildren(TypeName, AttributeName, AttributeValue);
            foreach (XMLNode node in children)
            {
                node.Parent = null;
                Children.Remove(node);
            }
        }
        public XMLNode GetChild(int Index)
        {
            if (Index < 0)
                return null;
            if (Children.Count > Index)
                return Children[Index];
            return null;
        }
        public List<XMLNode> GetChildren(string TypeName, string AttributeName = null, string AttributeValue = null)
        {
            List<XMLNode> chidren = new List<XMLNode>();
            foreach (XMLNode node in Children)
            {
                if (node.TypeName == TypeName)
                {
                    if (AttributeName != null && AttributeValue != null)
                    {
                        if (node.Attributes.ContainsKey(AttributeName) && node.Attributes[AttributeName] == AttributeValue)
                            chidren.Add(node);
                    }
                    else
                        chidren.Add(node);
                }
            }
            return chidren;
        }
    }
}
