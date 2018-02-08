import pandas
from sklearn import linear_model, feature_extraction

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
    
if __name__ == "__main__":
    # Read in the X data
    all_data = pandas.read_csv("data.csv")

    # Remove non-states
    all_data = all_data[pandas.notnull(all_data["STATE"])]

    # split between testing and training
    train_x = last_poll(all_data[all_data["TOPIC"] == '2012-president'])
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
    mod = linear_model.LinearRegression()
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
