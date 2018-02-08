
# coding: utf-8

# In[57]:

import pandas
from sklearn import linear_model, feature_extraction


# In[81]:

def categorical_features(row):
    d = {}
    d["STATE"] = row[1]["STATE"]
    return d

def last_poll(full_data):
    """
    Create feature from last poll in each state
    """
    
    # Only care about republicans
    repub = full_data[full_data["PARTY"] == "Rep"]

    # Sort by date
    chron = repub.sort_values(by="DATE", ascending=True)

    # Only keep the last one
    dedupe = chron.drop_duplicates(subset="STATE", keep="last")

    # Remove national polls
    return dedupe[dedupe["STATE"] != "US"]

def npolls(full_data, n=None):
    """
    Create feature from last poll in each state
    """
    if n == None:
        n = 1
    
    # Only care about republicans
    repub = full_data[full_data["PARTY"] == "Rep"]

    # Sort by date
    chron = repub.sort_values(by="DATE", ascending=True).groupby(["STATE"]).tail(n)

    # Only keep the last one
    #dedupe = chron.drop_duplicates(subset="STATE", keep="last")
    dedupe = chron #2540.5644747797082

    # Remove national polls
    return dedupe[dedupe["STATE"] != "US"]


# In[85]:

all_data = pandas.read_csv("data.csv")
all_data = all_data[pandas.notnull(all_data["STATE"])]
train_x = npolls(all_data[all_data["TOPIC"] == '2012-president'])
print(train_x)


# In[131]:

if __name__ == "__main__":
    # Read in the X data
    all_data = pandas.read_csv("data.csv")

    # Remove non-states
    all_data = all_data[pandas.notnull(all_data["STATE"])]

    # split between testing and training
    #train_x = npolls(all_data[all_data["TOPIC"] == '2012-president']) #2021.3667123442144
    #train_x = npolls(all_data[all_data["TOPIC"] == '2012-president'], 3) #2088.2307598216044
    #train_x = npolls(all_data[all_data["TOPIC"] == '2012-president'], 6) #2129.078770267785
    #train_x = npolls(all_data[all_data["TOPIC"] == '2012-president'], 9) #
    train_x = npolls(all_data[all_data["TOPIC"] == '2012-president'], 12) #
    train_x.set_index("STATE")
    
    test_x = last_poll(all_data[all_data["TOPIC"] == '2016-president'])
    test_x.set_index("STATE")
    
    # Read in the Y data
    y_data = pandas.read_csv("../data/2012_pres.csv", sep=';')
    y_data = y_data[y_data["PARTY"] == "R"]
    y_data = y_data[pandas.notnull(y_data["GENERAL %"])]
    y_data["GENERAL %"] = [float(x.replace(",", ".").replace("%", ""))
                           for x in y_data["GENERAL %"]]
    y_data["STATE"] = y_data["STATE ABBREVIATION"]
    y_data.set_index("STATE")

    backup = train_x
    train_x = y_data.merge(train_x, on="STATE",how='left')
    
    # make sure we have all states in the test data
    for ii in set(y_data.STATE) - set(test_x.STATE):
        new_row = pandas.DataFrame([{"STATE": ii}])
        test_x = test_x.append(new_row)

    # format the data for regression
    train_x = pandas.concat([train_x.STATE.astype(str).str.get_dummies(),
                             train_x], axis=1)
    test_x = pandas.concat([test_x.STATE.astype(str).str.get_dummies(),
                             test_x], axis=1)
        
    # handle missing data
    for dd in train_x, test_x:                
        dd["NOPOLL"] = pandas.isnull(dd["VALUE"])
        dd["VALUE"] = dd["VALUE"].fillna(0.0)
        
    # create feature list
    features = list(y_data.STATE)
    features.append("VALUE")
    features.append("NOPOLL")    
        
    # fit the regression
    #mod = linear_model.LinearRegression() #MSE = 2121.096713296368
    
    #mod = linear_model.Ridge(.5) #2113.8845100120075
    #mod = linear_model.Ridge(.8) #2112.848964277935     ***
    #mod = linear_model.Ridge(.2) #2116.8419143243755
    
    #mod = linear_model.Lasso(alpha=0.2) #2052.626114301892
    #mod = linear_model.Lasso(alpha=0.1) #2044.6961129089418   With 6 polls: 2017.6049243788343
    mod = linear_model.Lasso(alpha=0.3) #2072.707539293161   With 6 polls: 1897.0808958079351  With 9 polls: 1840.4118616586254  With 12 polls: 1824.9810324044872
    #mod = linear_model.Lasso(alpha=0.05) #2023.4943314517543 With 6 polls: 2011.2404532238545
    #mod = linear_model.Lasso(alpha=0.08) #2034.111415580015
    #mod = linear_model.Lasso(alpha=0.01) #2021.3667123442144     ***
        
    mod.fit(train_x[features], train_x["GENERAL %"])
    

    # Write out the model
    with open("model.txt", 'w') as out:
        out.write("BIAS\t%f\n" % mod.intercept_)
        for jj, kk in zip(features, mod.coef_):
            out.write("%s\t%f\n" % (jj, kk))
    
    # Write the predictions
    pred_test = mod.predict(test_x[features])
    with open("pred.txt", 'w') as out:
        for ss, vv in sorted(zip(list(test_x.STATE), pred_test)):
            out.write("%s\t%f\n" % (ss, vv))


# In[132]:

model = open('model.txt', "r")
pred = open('pred.txt', "r")

STATES = ['AL','AK','AZ','AR','CA','CO','CT','DE','DC','FL','GA','HI','ID','IL','IN','IA','KS','KY','LA','ME','MD','MA','MI','MN','MS','MO','MT','NE','NV','NH','NJ','NM','NY','NC','ND','OH','OK','OR','PA','RI','SC','SD','TN','TX','UT','VT','VA','WA','WV','WI','WY']
modlst = []
predlst = []
for line in model:
    a,b = line.split()
    if(a in STATES):
        modlst.append(float(b))

for line in pred:
    a,b = line.split()
    if(a in STATES):
        predlst.append(float(b))

model.close()
pred.close()

print(sum((modlst[i]-predlst[i])**2 for i in range(0,50))/50)

