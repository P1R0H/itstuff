<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0"
                xmlns="http://www.w3.org/1999/xhtml"
                xmlns:r="http://recipes.org">
    
    <xsl:output method="xml"
                doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
                doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
                encoding="UTF-8"
                indent="yes"
    />
    
    <xsl:template match="/">
        <html>
            <xsl:apply-templates select="r:collection" />
        </html>
    </xsl:template>
    
    <xsl:template match="r:collection">
        <head>
            <title>Collection of Recipes</title>
            <meta http-equiv="Content-Style-Type" content="text/css"/>
            <link rel="stylesheet" href="recipes.css" type="text/css" media="screen"/>
        </head>

        <body>
            <h1>Collection of Recipes</h1>
            <hr/><h2>List of Recipes</h2>
            <ul>
                <xsl:apply-templates select="r:recipe" mode="list"/>
            </ul>
            
            <h2>Recipes</h2>
            <xsl:apply-templates select="r:recipe"/>
        </body>
    </xsl:template>
    
    <xsl:template match="r:recipe" mode="list">
        <li>
            <a href="#{generate-id()}"><xsl:value-of select="r:title"/></a>
        </li>
    </xsl:template>
    
    <xsl:template match="r:recipe">
        <div>
            <hr/><a name="{generate-id()}" id="{generate-id()}"/>
            <h3><xsl:value-of select="r:title"/></h3>
            <h4>Ingredients</h4>
            <ul>
                <xsl:apply-templates select="r:ingredient"/>
            </ul>
            <xsl:apply-templates select="r:preparation"/>
        </div>
    </xsl:template>
    
    <xsl:template match="r:ingredient">
        <li>
            <strong>
                <xsl:value-of select="@name"/>
            </strong>: 
            <xsl:choose>
                <xsl:when test="@amount">
                    <xsl:value-of select="@amount"/>
                    <xsl:text> </xsl:text>
                    <xsl:value-of select="@unit"/>
                </xsl:when>
                <xsl:otherwise>
                    <h4>Ingredients</h4>
                    <ul>
                        <xsl:apply-templates select="r:ingredient"/>
                    </ul>
                    <xsl:apply-templates select="r:preparation"/>
                </xsl:otherwise>
            </xsl:choose>
        </li>
    </xsl:template>
    
    <xsl:template match="r:preparation">
        <h4>Preparation</h4>
        <ol>
            <xsl:apply-templates select="r:step"/>
        </ol>
    </xsl:template>
    
    <xsl:template match="r:step">
        <li>
            <xsl:value-of select="text()"/>
        </li>
    </xsl:template>
    
</xsl:stylesheet>
