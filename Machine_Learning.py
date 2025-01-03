# -*- coding: utf-8 -*-
"""
Created on Thu Sep 19 10:36:51 2024

@author: kmanc
"""

import requests
from bs4 import BeautifulSoup
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score

# Step 1: Web scraping function
def scrape_website(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')

    # Extracting all the paragraphs from the website
    paragraphs = soup.find_all('p')
    text_content = ' '.join([p.get_text() for p in paragraphs])
    
    return text_content

# Step 2: Define a few websites to scrape (for demonstration)
websites = [
    "https://en.wikipedia.org/wiki/Machine_learning",
    "https://en.wikipedia.org/wiki/Artificial_intelligence",
    "https://en.wikipedia.org/wiki/Data_science"
]

# Step 3: Scrape the websites
scraped_data = []
for site in websites:
    scraped_data.append(scrape_website(site))

# Step 4: Define some labels (1 for AI-related, 0 for non-AI-related) - Simulated dataset
labels = [1, 1, 0]  # Based on website content

# Step 5: Preprocess data and apply Machine Learning
vectorizer = TfidfVectorizer(stop_words='english')
X = vectorizer.fit_transform(scraped_data)  # Text vectorization

# Step 6: Split data into training and test sets
X_train, X_test, y_train, y_test = train_test_split(X, labels, test_size=0.3, random_state=42)

# Step 7: Train a classifier (Naive Bayes for text classification)
classifier = MultinomialNB()
classifier.fit(X_train, y_train)

# Step 8: Make predictions
predictions = classifier.predict(X_test)

# Step 9: Evaluate the model
accuracy = accuracy_score(y_test, predictions)
print(f"Model Accuracy: {accuracy * 100:.2f}%")

# Bonus: Predicting a new website content
new_website = "https://en.wikipedia.org/wiki/Deep_learning"
new_data = scrape_website(new_website)
new_data_transformed = vectorizer.transform([new_data])
prediction = classifier.predict(new_data_transformed)
print(f"Prediction for new website (1=AI, 0=Non-AI): {prediction[0]}")